#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "applications.h"
#include "queue.h"
#include "stack.h"

static void test_stack_basic(void) {
    Stack s;
    assert(stack_init(&s) == 0);
    int v;
    assert(stack_is_empty(&s));
    assert(stack_pop(&s, &v) == -1);
    assert(stack_peek(&s, &v) == -1);

    stack_push(&s, 1);
    stack_push(&s, 2);
    stack_push(&s, -1);                       /* -1 is a legal value */
    assert(stack_size(&s) == 3);
    assert(stack_peek(&s, &v) == 0 && v == -1);
    assert(stack_pop(&s, &v) == 0 && v == -1);
    assert(stack_pop(&s, &v) == 0 && v == 2);
    assert(stack_pop(&s, &v) == 0 && v == 1);
    assert(stack_is_empty(&s));
    stack_destroy(&s);
}

static void test_stack_grows(void) {
    Stack s;
    stack_init(&s);
    for (int i = 0; i < 1000; i++) {          /* well past the initial capacity */
        assert(stack_push(&s, i) == 0);
    }
    assert(stack_size(&s) == 1000);
    int v;
    for (int i = 999; i >= 0; i--) {
        assert(stack_pop(&s, &v) == 0 && v == i);
    }
    stack_destroy(&s);
}

static void test_queue(void) {
    Queue q;
    queue_init(&q);
    int v;
    assert(queue_is_empty(&q));
    assert(queue_dequeue(&q, &v) == -1);

    queue_enqueue(&q, 1);
    queue_enqueue(&q, 2);
    queue_enqueue(&q, 3);
    assert(queue_size(&q) == 3);
    assert(queue_peek(&q, &v) == 0 && v == 1);
    assert(queue_dequeue(&q, &v) == 0 && v == 1);   /* FIFO order */
    assert(queue_dequeue(&q, &v) == 0 && v == 2);

    queue_enqueue(&q, 4);
    assert(queue_dequeue(&q, &v) == 0 && v == 3);
    assert(queue_dequeue(&q, &v) == 0 && v == 4);
    assert(queue_is_empty(&q));
    assert(queue_dequeue(&q, &v) == -1);

    queue_enqueue(&q, 9);                           /* queue must still work after emptying */
    assert(queue_peek(&q, &v) == 0 && v == 9);
    queue_destroy(&q);
    assert(queue_is_empty(&q));
}

static void test_balanced(void) {
    assert(is_balanced(""));
    assert(is_balanced("()[]{}"));
    assert(is_balanced("{[()]}"));
    assert(is_balanced("(a + b) * [c]"));
    assert(!is_balanced("}[()]}"));             /* your original test string */
    assert(!is_balanced("(("));                 /* never closed */
    assert(!is_balanced("())"));                /* closer with nothing open */
    assert(!is_balanced("(]"));                 /* wrong kind */
    assert(!is_balanced("([)]"));               /* bad nesting */
}

static void test_postfix(void) {
    int r = 0;
    assert(eval_postfix("2 3 * 5 4 * + 9 -", &r) == EVAL_OK && r == 17);
    assert(eval_postfix("10 2 /", &r) == EVAL_OK && r == 5);
    assert(eval_postfix("12 30 +", &r) == EVAL_OK && r == 42);   /* multi-digit numbers */
    assert(eval_postfix("7", &r) == EVAL_OK && r == 7);
    assert(eval_postfix("4 0 /", &r) == EVAL_ERR_DIV_ZERO);
    assert(eval_postfix("+", &r) == EVAL_ERR_SYNTAX);            /* underflow */
    assert(eval_postfix("1 +", &r) == EVAL_ERR_SYNTAX);
    assert(eval_postfix("1 2", &r) == EVAL_ERR_SYNTAX);          /* leftover operand */
    assert(eval_postfix("", &r) == EVAL_ERR_SYNTAX);
    assert(eval_postfix("2 x +", &r) == EVAL_ERR_SYNTAX);
}

static void test_binary(void) {
    char buf[40];
    assert(to_binary(13, buf, sizeof buf) == 0 && strcmp(buf, "1101") == 0);
    assert(to_binary(0, buf, sizeof buf) == 0 && strcmp(buf, "0") == 0);
    assert(to_binary(1, buf, sizeof buf) == 0 && strcmp(buf, "1") == 0);
    assert(to_binary(255, buf, sizeof buf) == 0 && strcmp(buf, "11111111") == 0);
    char tiny[3];
    assert(to_binary(13, tiny, sizeof tiny) == -1);              /* too small, no overflow */
}

static void test_reverse_words(void) {
    char buf[64];
    assert(reverse_each_word("hello world", buf, sizeof buf) == 0);
    assert(strcmp(buf, "olleh dlrow") == 0);
    assert(reverse_each_word("a", buf, sizeof buf) == 0 && strcmp(buf, "a") == 0);
    assert(reverse_each_word("", buf, sizeof buf) == 0 && strcmp(buf, "") == 0);
    char tiny[4];
    assert(reverse_each_word("hello", tiny, sizeof tiny) == -1);
}

static void test_palindrome(void) {
    assert(is_palindrome_stack("RADAR"));
    assert(is_palindrome_stack("A man, a plan, a canal: Panama"));
    assert(is_palindrome_stack(""));
    assert(!is_palindrome_stack("hello"));
}

int main(void) {
    test_stack_basic();
    test_stack_grows();
    test_queue();
    test_balanced();
    test_postfix();
    test_binary();
    test_reverse_words();
    test_palindrome();
    printf("All tests passed.\n");
    return 0;
}
