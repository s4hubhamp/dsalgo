#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define STACK_MAX_CAPACITY 4

typedef struct stack
{
    int top;
    int elements[STACK_MAX_CAPACITY];
} stack;

void initialize_stack(stack *);
void push(int, stack *);
int pop(stack *);
void print(stack *);

int main()
{
    stack *s = malloc(sizeof(stack));
    if (s == NULL)
    {
        printf("Memory allocation failed for stack");
        return 1;
    }

    initialize_stack(s);
    print(s);

    push(1, s);
    push(2, s);
    push(3, s);
    push(4, s);
    print(s);
    push(4, s);

    pop(s);
    print(s);

    pop(s);
    pop(s);
    pop(s);
    print(s);

    pop(s);
    free(s);

    return 0;
}

void initialize_stack(stack *s)
{
    s->top = -1; // Stack is empty initially
}

void push(int x, stack *s)
{
    if (s->top == STACK_MAX_CAPACITY - 1)
    {
        printf("Error: Stack is full\n");
        return;
    }

    s->elements[++s->top] = x;
}

int pop(stack *s)
{
    if (s->top == -1)
    {
        printf("Error: Stack is empty\n");
        return INT_MIN;
    }

    int last = s->elements[s->top];
    s->top--;
    return last;
}

void print(stack *s)
{
    printf("\n********************************************");
    printf("\ntop: %d, ", s->top);
    printf("[ ");
    if (s->top > -1)
    {
        for (size_t i = 0; i <= s->top; i++)
        {
            printf("%d ", s->elements[i]);
        }
    }
    printf("]");
    printf("\n********************************************\n");
}