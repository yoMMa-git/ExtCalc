#include "stack.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenize.h"

Stack *create_stack(int size) {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->items = (Token *)malloc(sizeof(Token) * size);
  stack->size = size;
  stack->top = -1;
  return stack;
}

void push(Stack *stack, Token item) {
  if (!is_full(stack)) {
    stack->top++;
    stack->items[stack->top] = item;
  }
}

Token pop(Stack *stack) {
  Token item;
  item.type = TOK_END;
  if (!is_empty(stack)) {
    item = stack->items[stack->top];
    stack->top--;
  }
  return item;
}

int is_empty(Stack *stack) { return (stack->top == -1); }

int is_full(Stack *stack) { return (stack->top == stack->size - 1); }

void free_stack(Stack *stack) {
  free_tokens(stack->items);
  free(stack);
}
