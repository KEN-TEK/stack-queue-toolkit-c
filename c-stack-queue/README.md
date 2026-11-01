# Stack and Queue Toolkit in C

Two data structures built from scratch, plus five classic problems solved with them.
Standard C11, no warnings under `-Wall -Wextra -Wpedantic`, and clean under
AddressSanitizer and UndefinedBehaviorSanitizer.

## What it demonstrates

| Concept | Where |
|---|---|
| Dynamic array that doubles when full (`realloc` done safely) | `stack.c` |
| Linked queue with front and rear pointers, O(1) enqueue and dequeue | `queue.c` |
| Error handling without magic values: results come back through an output pointer, so `-1` is a legal stored value | `stack_pop`, `queue_dequeue` |
| Stack applications: bracket matching, postfix evaluation, base conversion, word reversal, palindromes | `applications.c` |
| Input validation (division by zero, operand underflow, buffer too small) | `eval_postfix`, `to_binary` |
| No global state: each stack or queue is a value you create, so you can have many | all |

## Files

| File | Contents |
|---|---|
| `stack.h`, `stack.c` | Growable int stack |
| `queue.h`, `queue.c` | Linked FIFO queue |
| `applications.h`, `applications.c` | Problems solved with the stack |
| `main.c` | Demo, including a printer-job queue |
| `tests.c` | Assertion-based tests |

## The problems

- **`is_balanced`**: checks `()`, `[]`, `{}` for correct opening, closing and nesting. Catches the three failure kinds: a closer with nothing open, the wrong kind of bracket, and brackets never closed.
- **`eval_postfix`**: evaluates e.g. `"2 3 * 5 4 * + 9 -"` (= 17). Returns a status: OK, syntax error, or division by zero.
- **`to_binary`**: pushes remainders of repeated division by 2, then pops them to get the digits in the right order.
- **`reverse_each_word`**: pushes letters, pops at each space.
- **`is_palindrome_stack`**: ignores case and punctuation.

## Build and run

```bash
make          # builds ./demo and ./tests
make run      # demo
make test     # tests
make check    # tests again with sanitizers (finds leaks and memory errors)
make clean
```

## Design notes

- **Why an output pointer instead of returning the value?** If `pop` returned `-1` for "empty", you could never tell an empty stack from a stored `-1`. Returning a status and writing the value separately removes the ambiguity.
- **Why does `stack_push` keep the old buffer when `realloc` fails?** Assigning `realloc`'s result straight back to `s->items` would lose the only pointer to the old memory on failure. A temporary pointer avoids that leak.
- **Why is the queue's `rear` set to `NULL` when it empties?** Otherwise it would point at freed memory (a dangling pointer) and the next enqueue would write into it.

## Possible next steps

- Make the containers generic with `void *`.
- Implement a queue using two stacks, and a circular array queue.
- Add infix-to-postfix conversion, so you can evaluate `3 + 4 * 2` directly.
