#ifndef POLISH_H
#define POLISH_H

#include "stack.h"
#include "tokenize.h"

/*
convert_to_polish - принимает на вход массив лексем, преобразует в польскую
нотацию calculate - принимает на вход массив в польской нотации и х, для
которого нужно посчитать значение, возвращает результат в double
*/

Token *convert_to_polish(Token *mass);
void deikstra(Token *mass, int i, Stack *stack_res, Stack *stack_operands);
double calculate(Token *mass, double val, int *flag);
int calculate_res(char *expr, double *res);
void check_for_number(Token *mass, int i, Stack *stack, double val);
void check_for_second_priority(Token *mass, int i, Stack *stack, int *flag);
void check_for_third_priority(Token *mass, int i, Stack *stack, int *flag);
void check_for_function(Token *mass, int i, Stack *stack);

#endif
