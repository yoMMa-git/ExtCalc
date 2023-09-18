#ifndef STACK_H
#define STACK_H

#include "tokenize.h"
/*
Для реализации стека нам нужно определить, какой тип данных мы будем
использовать для хранения элементов стека. В данном случае, поскольку мы
работаем с токенами, так что давайте использовать массив Token для хранения
элементов стека.
*/

/*
Мы можем определить структуру Stack, которая будет содержать указатель на массив
Token, размер стека и текущую позицию в стеке.
*/

typedef struct {
  Token *items;
  int size;
  int top;
} Stack;

/*

Нам также понадобится несколько функций для работы со стеком:
create_stack - функция для создания стека с заданным размером
push - функция для добавления элемента в стек
pop - функция для удаления и возврата последнего элемента стека
is_empty - функция для проверки, пуст ли стек
is_full - функция для проверки, заполнен ли стек
void free_stack - для очистки стека от утечек

*/

Stack *create_stack(int size);
void push(Stack *stack, Token item);
Token pop(Stack *stack);
int is_empty(Stack *stack);
int is_full(Stack *stack);
void free_stack(Stack *stack);

#endif
