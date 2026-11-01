#include <stdio.h>

#include "applications.h"
#include "queue.h"
#include "stack.h"

static void demo_stack(void) {
    printf("--- Stack ---\n");
    Stack s;
    stack_init(&s);
    for (int i = 1; i <= 4; i++) {
        stack_push(&s, i * 10);
    }
    int top;
    stack_peek(&s, &top);
    printf("size %zu, top %d\n", stack_size(&s), top);
    while (stack_pop(&s, &top) == 0) {
        printf("popped %d\n", top);
    }
    printf("pop on empty stack returns %d\n", stack_pop(&s, &top));
    stack_destroy(&s);
}

static void demo_printer_queue(void) {
    printf("\n--- Queue: printer jobs ---\n");
    Queue q;
    queue_init(&q);
    queue_enqueue(&q, 101);
    queue_enqueue(&q, 102);
    queue_enqueue(&q, 103);
    queue_print(&q);

    int job;
    while (queue_dequeue(&q, &job) == 0) {
        printf("printing job %d (%zu waiting)\n", job, queue_size(&q));
    }
    queue_destroy(&q);
}

static void demo_applications(void) {
    printf("\n--- Applications ---\n");

    const char *exprs[] = {"{[()]}", "(a + b) * [c - d]", "}[()]}", "((]"};
    for (size_t i = 0; i < sizeof exprs / sizeof exprs[0]; i++) {
        printf("balanced \"%s\": %s\n", exprs[i], is_balanced(exprs[i]) ? "yes" : "no");
    }

    int value;
    EvalStatus st = eval_postfix("2 3 * 5 4 * + 9 -", &value);
    printf("postfix \"2 3 * 5 4 * + 9 -\" = %d (status %d)\n", value, st);
    st = eval_postfix("4 0 /", &value);
    printf("postfix \"4 0 /\" status %d (2 = division by zero)\n", st);

    char buf[64];
    to_binary(13, buf, sizeof buf);
    printf("13 in binary: %s\n", buf);

    reverse_each_word("stacks reverse things", buf, sizeof buf);
    printf("each word reversed: %s\n", buf);

    printf("\"A man, a plan, a canal: Panama\" palindrome: %s\n",
           is_palindrome_stack("A man, a plan, a canal: Panama") ? "yes" : "no");
}

int main(void) {
    demo_stack();
    demo_printer_queue();
    demo_applications();
    return 0;
}
