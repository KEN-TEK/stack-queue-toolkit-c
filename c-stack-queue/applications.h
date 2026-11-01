#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include <stddef.h>

/* Classic problems solved with the Stack. */

/* 1 if every (), [], {} is correctly opened, closed and nested; other characters are ignored. */
int is_balanced(const char *expr);

typedef enum {
    EVAL_OK = 0,
    EVAL_ERR_SYNTAX,        /* bad token, too few or too many operands */
    EVAL_ERR_DIV_ZERO
} EvalStatus;

/*
 * Evaluates a postfix expression. Operands are non-negative integers and every
 * token is separated by spaces, e.g. "2 3 * 5 4 * + 9 -" (= 17).
 * Supported operators: + - * /
 */
EvalStatus eval_postfix(const char *expr, int *result);

/* Writes n in binary into out (NUL-terminated). Returns 0, or -1 if out is too small. */
int to_binary(unsigned int n, char *out, size_t out_size);

/* Reverses the letters of each word but keeps word order. Returns 0, or -1 if out is too small. */
int reverse_each_word(const char *in, char *out, size_t out_size);

/* 1 if the text reads the same both ways, ignoring case and non-alphanumeric characters. */
int is_palindrome_stack(const char *s);

#endif
