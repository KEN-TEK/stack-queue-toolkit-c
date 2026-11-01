#include "applications.h"

#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

int is_balanced(const char *expr) {
    Stack s;
    if (stack_init(&s) != 0) {
        return 0;
    }

    int ok = 1;
    for (const char *p = expr; *p != '\0' && ok; p++) {
        char c = *p;
        if (c == '(' || c == '[' || c == '{') {
            if (stack_push(&s, c) != 0) {
                ok = 0;
            }
        } else if (c == ')' || c == ']' || c == '}') {
            int open;
            if (stack_pop(&s, &open) != 0) {
                ok = 0;                                  /* closer with nothing to close */
            } else if ((c == ')' && open != '(') ||
                       (c == ']' && open != '[') ||
                       (c == '}' && open != '{')) {
                ok = 0;                                  /* wrong kind of bracket */
            }
        }
    }

    if (!stack_is_empty(&s)) {
        ok = 0;                                          /* something was never closed */
    }
    stack_destroy(&s);
    return ok;
}

EvalStatus eval_postfix(const char *expr, int *result) {
    Stack s;
    if (stack_init(&s) != 0) {
        return EVAL_ERR_SYNTAX;
    }

    EvalStatus status = EVAL_OK;
    const char *p = expr;

    while (*p != '\0' && status == EVAL_OK) {
        if (isspace((unsigned char)*p)) {
            p++;
        } else if (isdigit((unsigned char)*p)) {
            long value = 0;
            while (isdigit((unsigned char)*p)) {
                value = value * 10 + (*p - '0');
                if (value > INT_MAX) {
                    status = EVAL_ERR_SYNTAX;
                    break;
                }
                p++;
            }
            if (status == EVAL_OK && stack_push(&s, (int)value) != 0) {
                status = EVAL_ERR_SYNTAX;
            }
        } else if (*p == '+' || *p == '-' || *p == '*' || *p == '/') {
            int b, a;                                    /* b is the top: it was pushed last */
            if (stack_pop(&s, &b) != 0 || stack_pop(&s, &a) != 0) {
                status = EVAL_ERR_SYNTAX;
            } else {
                int r = 0;
                switch (*p) {
                    case '+': r = a + b; break;
                    case '-': r = a - b; break;
                    case '*': r = a * b; break;
                    case '/':
                        if (b == 0) {
                            status = EVAL_ERR_DIV_ZERO;
                        } else {
                            r = a / b;
                        }
                        break;
                }
                if (status == EVAL_OK && stack_push(&s, r) != 0) {
                    status = EVAL_ERR_SYNTAX;
                }
            }
            p++;
        } else {
            status = EVAL_ERR_SYNTAX;                    /* unknown character */
        }
    }

    if (status == EVAL_OK) {
        if (stack_size(&s) != 1 || stack_pop(&s, result) != 0) {
            status = EVAL_ERR_SYNTAX;                    /* empty, or leftover operands */
        }
    }
    stack_destroy(&s);
    return status;
}

int to_binary(unsigned int n, char *out, size_t out_size) {
    Stack s;
    if (stack_init(&s) != 0) {
        return -1;
    }

    if (n == 0) {
        stack_push(&s, 0);
    }
    while (n > 0) {
        if (stack_push(&s, (int)(n % 2)) != 0) {
            stack_destroy(&s);
            return -1;
        }
        n /= 2;
    }

    if (stack_size(&s) + 1 > out_size) {                 /* digits plus the terminating NUL */
        stack_destroy(&s);
        return -1;
    }

    size_t i = 0;
    int bit;
    while (stack_pop(&s, &bit) == 0) {                   /* remainders come out most significant first */
        out[i++] = (char)('0' + bit);
    }
    out[i] = '\0';
    stack_destroy(&s);
    return 0;
}

int reverse_each_word(const char *in, char *out, size_t out_size) {
    if (strlen(in) + 1 > out_size) {
        return -1;
    }

    Stack s;
    if (stack_init(&s) != 0) {
        return -1;
    }

    size_t j = 0;
    for (size_t i = 0;; i++) {
        if (in[i] == ' ' || in[i] == '\0') {
            int c;
            while (stack_pop(&s, &c) == 0) {
                out[j++] = (char)c;
            }
            if (in[i] == '\0') {
                break;
            }
            out[j++] = ' ';
        } else if (stack_push(&s, (unsigned char)in[i]) != 0) {
            stack_destroy(&s);
            return -1;
        }
    }
    out[j] = '\0';
    stack_destroy(&s);
    return 0;
}

int is_palindrome_stack(const char *s) {
    Stack st;
    if (stack_init(&st) != 0) {
        return 0;
    }

    for (const char *p = s; *p != '\0'; p++) {           /* pass 1: push cleaned characters */
        if (isalnum((unsigned char)*p)) {
            if (stack_push(&st, tolower((unsigned char)*p)) != 0) {
                stack_destroy(&st);
                return 0;
            }
        }
    }

    int result = 1;
    for (const char *p = s; *p != '\0' && result; p++) { /* pass 2: pop gives the reverse order */
        if (isalnum((unsigned char)*p)) {
            int c;
            stack_pop(&st, &c);
            if (c != tolower((unsigned char)*p)) {
                result = 0;
            }
        }
    }
    stack_destroy(&st);
    return result;
}
