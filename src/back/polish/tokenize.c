#include "tokenize.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция проверки, является ли символ цифрой
int is_digit(char c) { return (c >= '0' && c <= '9'); }

// Функция, преобразующая строку в число
double parse_number(const char *expr, int *pos) {
  double result = 0.0;
  int digits = 0;

  // Читаем целую часть числа
  while (is_digit(expr[*pos])) {
    result = result * 10.0 + (double)(expr[*pos] - '0');
    (*pos)++;
    digits++;
  }

  // Если дальше идет десятичная часть, то читаем ее тоже
  if (expr[*pos] == '.') {
    (*pos)++;
    double factor = 0.1;
    while (is_digit(expr[*pos])) {
      result += (double)(expr[*pos] - '0') * factor;
      factor *= 0.1;
      (*pos)++;
      digits++;
    }
  }
  return result;
}

// Функция, преобразующая char в double
double parse_string(const char *expr, const int *pos) {
  double result = (double)(expr[*pos]);

  return result;
}

// Функция, преобразующая строку в лексему
Token parse_token(const char *expr, int *pos) {
  Token token;
  token.type = TOK_END;
  token.value = 0.0;
  // Пропускаем пробельные символы
  while (expr[*pos] == ' ' || expr[*pos] == '\t') {
    (*pos)++;
  }
  int flag_check = 0;

  // Если следующий символ - цифра, то парсим число
  if_numb(expr, &flag_check, &token, pos);
  // Иначе, если следующий символ - оператор, то возвращаем соответствующую
  // лексему
  if_operand_second_priority(expr, &flag_check, &token, pos);
  if_operand_third_priority(expr, &flag_check, &token, pos);
  // Иначе, если следующие символы - функция, то парсим ее
  if_function(expr, &flag_check, &token, pos);
  // Иначе, если следующий символ - скобка, то возвращаем
  // соответствующую лексему
  if_brackets(expr, &flag_check, &token, pos);
  //Иначе считываем переменную
  if_variable(expr, &flag_check, &token, pos);
  //Проверяем были ли вообще какие-то операции
  if_invalid(&flag_check, &token, pos);
  return token;
}

// Функция, осуществляющая лексический анализ строки
Token *tokenize(const char *expr) {
  int len = strlen(expr);
  int pos = 0;
  Token *tokens = (Token *)malloc(sizeof(Token) * (len + 1));
  int token_count = 0;
  // Читаем лексемы из строки, пока не достигнут конец строки
  while (pos < len) {
    tokens[token_count++] = parse_token(expr, &pos);
  }
  // Добавляем в конец массива лексему TOK_END
  tokens[token_count].type = TOK_END;
  tokens[token_count].value = 0.0;
  return tokens;
}

// Функция освобождения памяти, занятой массивом лексем
void free_tokens(Token *tokens) { free(tokens); }

//Предобработка на скобки, недопустимые символы и числа
int raise_error(Token *mass) {
  int left_bracket = 0;
  int right_bracket = 0;
  int flag_invalid = 0;
  int nums = 0;
  for (int i = 0; mass[i].type != TOK_END; i++) {
    if (mass[i].type == TOK_LPAREN) left_bracket++;
    if (mass[i].type == TOK_RPAREN) right_bracket++;
    if (mass[i].type == TOK_INVALID) flag_invalid = 1;
    if (mass[i].type == TOK_NUMBER || mass[i].type == TOK_VARIABLE) nums++;
  }
  if (left_bracket != right_bracket) flag_invalid = 1;
  if (nums == 0) flag_invalid = 2;
  return flag_invalid;
}

void if_numb(const char *expr, int *flag_check, Token *token, int *pos) {
  // Если следующий символ - цифра, то парсим число
  if (is_digit(expr[*pos]) && *flag_check == 0) {
    (*token).type = TOK_NUMBER;
    (*token).value = parse_number(expr, pos);
    (*token).flag_function = 0;
    *flag_check = 1;
  }
}

void if_operand_second_priority(const char *expr, int *flag_check, Token *token,
                                int *pos) {
  if (expr[*pos] == '+' && *flag_check == 0) {
    char prev_char = expr[*pos - 1];
    // Распознаем унарный плюс
    if (*pos == 0 || prev_char == '(' || prev_char == '+' || prev_char == '-' ||
        prev_char == '*' || prev_char == '/') {
      // плюс в начале строки или предыдущий символ является оператором,
      // значит, плюс унарный
      (*token).flag_function = 2;
      (*token).type = TOK_OP_POS;
      (*pos)++;
    } else {
      // бинарный плюс
      (*token).type = TOK_OP_PLUS;
      (*token).flag_function = 2;
      (*pos)++;
    }
    *flag_check = 1;
  }
  if (expr[*pos] == '-' && *flag_check == 0) {
    char prev_char = expr[*pos - 1];
    // Распознаем унарный минус
    if (*pos == 0 || prev_char == '(' || prev_char == '+' || prev_char == '-' ||
        prev_char == '*' || prev_char == '/') {
      // минус в начале строки или предыдущий символ является оператором,
      // значит, минус унарный
      (*token).flag_function = 2;
      (*token).type = TOK_OP_NEG;
      (*pos)++;
    } else {
      // бинарный минус
      (*token).flag_function = 2;
      (*token).type = TOK_OP_MINUS;
      (*pos)++;
    }
    *flag_check = 1;
  }
}

void if_operand_third_priority(const char *expr, int *flag_check, Token *token,
                               int *pos) {
  if (expr[*pos] == '*' && *flag_check == 0) {
    (*token).type = TOK_OP_MULT;
    (*token).flag_function = 3;
    *flag_check = 1;
    (*pos)++;
  }

  if (expr[*pos] == '/' && *flag_check == 0) {
    (*token).type = TOK_OP_DIV;
    (*token).flag_function = 3;
    *flag_check = 1;
    (*pos)++;
  }

  if (strncmp(expr + *pos, "mod", 3) == 0 && *flag_check == 0) {
    (*token).type = TOK_OP_MOD;
    (*token).flag_function = 3;
    *flag_check = 1;
    (*pos) += 3;
  }
}

void if_function(const char *expr, int *flag_check, Token *token, int *pos) {
  if (strncmp(expr + *pos, "sin", 3) == 0 && *flag_check == 0) {
    (*token).type = TOK_FUNC_SIN;
    (*token).flag_function = 4;
    *flag_check = 1;
    (*pos) += 3;
  }
  if (strncmp(expr + *pos, "asin", 4) == 0 && *flag_check == 0) {
    (*token).type = TOK_FUNC_ASIN;
    (*token).flag_function = 4;
    *flag_check = 1;
    (*pos) += 4;
  }
  if (strncmp(expr + *pos, "cos", 3) == 0 && *flag_check == 0) {
    (*token).type = TOK_FUNC_COS;
    (*token).flag_function = 4;
    *flag_check = 1;
    (*pos) += 3;
  }
  if (strncmp(expr + *pos, "acos", 4) == 0 && *flag_check == 0) {
    (*token).type = TOK_FUNC_ACOS;
    (*token).flag_function = 4;
    *flag_check = 1;
    (*pos) += 4;
  }
  if (strncmp(expr + *pos, "tan", 3) == 0 && *flag_check == 0) {
    (*token).type = TOK_FUNC_TG;
    (*token).flag_function = 4;
    *flag_check = 1;
    (*pos) += 3;
  }
  if (strncmp(expr + *pos, "atan", 4) == 0 && *flag_check == 0) {
    (*token).type = TOK_FUNC_ATG;
    (*token).flag_function = 4;
    *flag_check = 1;
    (*pos) += 4;
  }
  if (strncmp(expr + *pos, "sqrt", 4) == 0 && *flag_check == 0) {
    (*token).type = TOK_FUNC_SQRT;
    (*token).flag_function = 4;
    *flag_check = 1;
    (*pos) += 4;
  }
  if (strncmp(expr + *pos, "log", 3) == 0 && *flag_check == 0) {
    (*token).type = TOK_FUNC_LOG;
    (*token).flag_function = 4;
    *flag_check = 1;
    (*pos) += 3;
  }

  if (strncmp(expr + *pos, "ln", 2) == 0 && *flag_check == 0) {
    (*token).type = TOK_FUNC_LN;
    (*token).flag_function = 4;
    *flag_check = 1;
    (*pos) += 2;
  }

  if (strncmp(expr + *pos, "^", 1) == 0 && *flag_check == 0) {
    (*token).type = TOK_FUNC_POW;
    (*token).flag_function = 4;
    *flag_check = 1;
    (*pos) += 1;
  }
}

void if_brackets(const char *expr, int *flag_check, Token *token, int *pos) {
  if (expr[*pos] == '(' && *flag_check == 0) {
    (*token).type = TOK_LPAREN;
    (*token).flag_function = 1;
    *flag_check = 1;
    (*pos)++;
  }
  if (expr[*pos] == ')' && *flag_check == 0) {
    (*token).type = TOK_RPAREN;
    (*token).flag_function = 5;
    *flag_check = 1;
    (*pos)++;
  }
}

void if_variable(const char *expr, int *flag_check, Token *token, int *pos) {
  if ((expr[*pos] == 'x' || expr[*pos] == 'X') && *flag_check == 0) {
    (*token).type = TOK_VARIABLE;
    (*token).value = parse_string(expr, pos);
    (*token).flag_function = -1;
    *flag_check = 1;
    (*pos)++;
  }
}

void if_invalid(const int *flag_check, Token *token, int *pos) {
  if (*flag_check == 0) {
    (*token).type = TOK_INVALID;
    (*token).flag_function = -10;
    (*pos)++;
  }
}
