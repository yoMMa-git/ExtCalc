#include "polish.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "tokenize.h"
#define STACK_SIZE 200

/*
        Создаем два стека: один для хранения самой результирующей строки, второй
   для хранения операндов

        -1|0: значит ввели х или просто число, при -1 задаем value
   соответсвуюющего значения массива 2: Операции  + - 3: Операции / * 4:
   Опрерации функций Если флаг функтор от 2 до 4, то действуем по алгоритму
   пункты 3 и 4


        Приоритет хранится в flag_function:
        -1: переменная х
        0: число
        1: Левая скобка (
        2: Операции  + -
        3: Операции / *
        4: Опрерации функций
        5: Правая скобка )
        Если флаг функтор от 2 до 4, то действуем по алгоритму:

        Принцип работы алгоритма Дейкстра:
        1)Проходим исходную строку;
        2)При нахождении числа, заносим его в выходную строку;
        3)При нахождении оператора, заносим его в стек;
        4)Выталкиваем в выходную строку из стека все операторы, имеющие
   приоритет выше рассматриваемого; 5)При нахождении открывающейся скобки,
   заносим её в стек; 6)При нахождении закрывающей скобки, выталкиваем из стека
   все операторы до открывающейся скобки, а открывающуюся скобку удаляем из
   стека.
*/

Token *convert_to_polish(Token *mass) {
  Stack *stack_res = create_stack(STACK_SIZE);
  Stack *stack_operands = create_stack(STACK_SIZE);
  Token *res_mass = (Token *)malloc(sizeof(Token));

  for (int i = 0; mass[i].type != TOK_END; i++)
    deikstra(mass, i, stack_res, stack_operands);
  // Последняя проверка стека операндов. Считывание строки закончилось, а в
  // стеке операндов есть значения.
  if (!is_empty(stack_operands))
    while (!is_empty(stack_operands)) {
      Token x = pop(stack_operands);
      if (x.type != TOK_LPAREN) push(stack_res, x);
    }

  void *tmp = realloc(res_mass, (stack_res->top + 2) * sizeof(Token));
  if (NULL != tmp) res_mass = tmp;

  for (int i = 0; i < stack_res->top + 1; i++)
    res_mass[i] = stack_res->items[i];
  res_mass[stack_res->top + 1].type = TOK_END;
  free_stack(stack_res);
  free_stack(stack_operands);
  return res_mass;
}

void deikstra(Token *mass, int i, Stack *stack_res, Stack *stack_operands) {
  if (mass[i].flag_function == 0 || mass[i].flag_function == -1) {
    push(stack_res, mass[i]);
  }
  if (mass[i].flag_function > 1 && mass[i].flag_function < 5) {
    if (is_empty(stack_operands) ||
        stack_operands->items[stack_operands->top].flag_function <
            mass[i].flag_function)
      push(stack_operands, mass[i]);
    else {
      while (stack_operands->items[stack_operands->top].flag_function >=
             mass[i].flag_function) {
        if (is_empty(stack_operands)) break;
        push(stack_res, pop(stack_operands));
      }
      push(stack_operands, mass[i]);
    }
  }
  /* Проверка на скобки:
      левая скобка: просто кладем на стек операндов
      правая скобка: освобождаем стек с операндами до тех пор, пока не
     встретили ( . Затем снимаем саму ( со стека
  */
  if (mass[i].type == TOK_LPAREN) {
    push(stack_operands, mass[i]);
  }
  if (mass[i].type == TOK_RPAREN) {
    while (stack_operands->items[stack_operands->top].type != TOK_LPAREN) {
      Token x = pop(stack_operands);
      if (x.type != TOK_LPAREN) push(stack_res, x);
    }
    pop(stack_operands);
  }
}

double calculate(Token *mass, double val, int *flag) {
  Stack *stack = create_stack(STACK_SIZE);
  for (int i = 0; mass[i].type != TOK_END; i++) {
    check_for_number(mass, i, stack, val);
    check_for_second_priority(mass, i, stack, flag);
    check_for_third_priority(mass, i, stack, flag);
    check_for_function(mass, i, stack);
  }
  double res = 0;
  if (stack->top == 0) {
    res = stack->items[stack->top].value;
  }
  free_stack(stack);
  return res;
}

int calculate_res(char *expr, double *res_val) {
  Token *tokens = tokenize(expr);
  int flag = raise_error(tokens);
  int res_flag = 0;
  int flag_calc = 0;
  double x = 10;
  if (flag == 0) {
    Token *res = convert_to_polish(tokens);
    double temp = calculate(res, x, &flag_calc);
    if (flag_calc == 0) {
      *res_val = temp;
    } else {
      res_flag = 1;
    }
    free_tokens(res);
  } else {
    res_flag = 1;
  }
  free_tokens(tokens);

  return res_flag;
}

void check_for_number(Token *mass, int i, Stack *stack, double val) {
  if (mass[i].flag_function == 0 || mass[i].flag_function == -1) {
    if (mass[i].flag_function == -1) mass[i].value = val;
    push(stack, mass[i]);
  }
}

void check_for_second_priority(Token *mass, int i, Stack *stack, int *flag) {
  if (mass[i].flag_function == 2) {
    if (mass[i].type == TOK_OP_MINUS || mass[i].type == TOK_OP_PLUS) {
      Token y = pop(stack);
      if (stack->top == -1) *flag = 1;
      Token x = pop(stack);
      Token res;
      if (mass[i].type == TOK_OP_MINUS) res.value = x.value - y.value;
      if (mass[i].type == TOK_OP_PLUS) res.value = x.value + y.value;
      res.type = TOK_NUMBER;
      res.flag_function = 0;
      push(stack, res);
    } else if (mass[i].type == TOK_OP_NEG) {
      Token x = pop(stack);
      Token res;
      res.value = x.value * (-1);
      res.type = TOK_NUMBER;
      res.flag_function = 0;
      push(stack, res);
    } else if (mass[i].type == TOK_OP_POS) {
      Token x = pop(stack);
      Token res;
      res.value = x.value;
      res.type = TOK_NUMBER;
      res.flag_function = 0;
      push(stack, res);
    }
  }
}

void check_for_third_priority(Token *mass, int i, Stack *stack, int *flag) {
  if (mass[i].flag_function == 3) {
    Token y = pop(stack);
    if (stack->top == -1) *flag = 1;
    Token x = pop(stack);
    Token res;
    if (mass[i].type == TOK_OP_MULT) res.value = x.value * y.value;
    if (mass[i].type == TOK_OP_DIV) res.value = x.value / y.value;
    if (mass[i].type == TOK_OP_MOD) res.value = (int)x.value % (int)y.value;
    res.type = TOK_NUMBER;
    res.flag_function = 0;
    push(stack, res);
  }
}

void check_for_function(Token *mass, int i, Stack *stack) {
  if (mass[i].flag_function == 4) {
    Token x = pop(stack);
    Token res;
    if (mass[i].type == TOK_FUNC_SIN) res.value = sin(x.value);
    if (mass[i].type == TOK_FUNC_COS) res.value = cos(x.value);
    if (mass[i].type == TOK_FUNC_TG) {
      res.value = tan(x.value);
    }

    if (mass[i].type == TOK_FUNC_ATG) res.value = atan(x.value);

    if (mass[i].type == TOK_FUNC_SQRT) {
      if (x.value < 0)
        res.value = NAN;
      else
        res.value = sqrt(x.value);
    }
    if (mass[i].type == TOK_FUNC_LN) {
      if (x.value < 0)
        res.value = NAN;
      else
        res.value = log(x.value);
    }
    if (mass[i].type == TOK_FUNC_LOG) {
      if (x.value < 0)
        res.value = NAN;
      else
        res.value = log10(x.value);
    }
    if (mass[i].type == TOK_FUNC_POW) {
      Token y = pop(stack);
      res.value = pow(y.value, x.value);
    }
    res.type = TOK_NUMBER;
    res.flag_function = 0;
    push(stack, res);
  }
}
