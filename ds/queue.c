#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define QUEUE_MAX_CAPACITY 100

typedef struct queue
{
    int tail;
    int elements[QUEUE_MAX_CAPACITY];
} queue;

void initialize_queue(queue *);
void enque(int, queue *);
int dequeue(queue *);
void print(queue *);

int main()
{
    queue *s = malloc(sizeof(queue));
    if (s == NULL)
    {
        printf("Memory allocation failed for queue");
        return 1;
    }

    initialize_queue(s);
    print(s);

    enque(1, s);
    enque(2, s);
    enque(3, s);
    enque(4, s);
    print(s);

    dequeue(s);
    print(s);

    dequeue(s);
    dequeue(s);
    dequeue(s);
    print(s);

    dequeue(s);
    free(s);

    return 0;
}

void initialize_queue(queue *s)
{
    s->tail = -1;
}

void enque(int x, queue *s)
{
    if (s->tail == QUEUE_MAX_CAPACITY - 1)
    {
        printf("Error: Queue is full\n");
        return;
    }

    s->elements[++s->tail] = x;
}

int dequeue(queue *s)
{
    if (s->tail == -1)
    {
        printf("Error: Queue is empty\n");
        return INT_MIN;
    }

    int first = s->elements[0];
    for (size_t i = 0; i < s->tail; i++)
    {
        s->elements[i] = s->elements[i + 1];
    }
    s->tail--;
    return first;
}

void print(queue *s)
{
    printf("\n********************************************");
    printf("\n tail: %d, ", s->tail);
    printf("[ ");
    if (s->tail > -1)
    {
        for (size_t i = 0; i <= s->tail; i++)
        {
            printf("%d ", s->elements[i]);
        }
    }
    printf("]");
    printf("\n********************************************\n");
}