#ifndef TOKENIZE_H
#define TOKENIZE_H

/* Перечисление TokenType определяет все возможные типы лексем,
которые мы можем получить при анализе строки выражения.
Это включает числа, операторы (сложение, вычитание, умножение, деление,
возведение в степень), а также открывающую и закрывающую скобки.
*/
typedef enum {
  TOK_NUMBER,
  TOK_OP_PLUS,
  TOK_OP_MINUS,
  TOK_OP_MULT,
  TOK_OP_DIV,
  TOK_OP_NEG,
  TOK_OP_POS,
  TOK_OP_MOD,
  TOK_LPAREN,
  TOK_RPAREN,
  TOK_VARIABLE,
  TOK_FUNC_SIN,
  TOK_FUNC_ASIN,
  TOK_FUNC_COS,
  TOK_FUNC_ACOS,
  TOK_FUNC_TG,
  TOK_FUNC_ATG,
  TOK_FUNC_SQRT,
  TOK_FUNC_LN,
  TOK_FUNC_LOG,
  TOK_FUNC_POW,
  TOK_INVALID,
  TOK_END
} TokenType2;

/* Структура Token представляет лексему. Она содержит
тип лексемы и ее значение (если это число). */

typedef struct {
  TokenType2 type;
  double value;
  int flag_function;
} Token;

/* Структура Tokenizer используется для хранения информации о строке выражения,
 которую мы анализируем, и текущей позиции в этой строке. */

typedef struct {
  const char *expr;
  int pos;
} Tokenizer;

/* Функция tokenize принимает строку выражения и
возвращает указатель на массив лексем (Token*),
которые мы получили в результате анализа строки. */

Token *tokenize(const char *expr);
int raise_error(Token *mass);

/* Функция free_tokens используется для освобождения памяти,
выделенной под массив лексем после того, как он больше не нужен. */

void free_tokens(Token *tokens);

void if_numb(const char *expr, int *flag_check, Token *token, int *pos);
void if_operand_second_priority(const char *expr, int *flag_check, Token *token,
                                int *pos);
void if_operand_third_priority(const char *expr, int *flag_check, Token *token,
                               int *pos);
void if_function(const char *expr, int *flag_check, Token *token, int *pos);
double parse_string(const char *expr, const int *pos);
void if_brackets(const char *expr, int *flag_check, Token *token, int *pos);
void if_variable(const char *expr, int *flag_check, Token *token, int *pos);
void if_invalid(const int *flag_check, Token *token, int *pos);

#endif
