// This is the priority queue by using sorted array

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define PRIORITY_QUEUE_MAX_SIZE 20

typedef struct priority_queue
{
    int elements[PRIORITY_QUEUE_MAX_SIZE];
    int size;
} priority_queue;

int empty(priority_queue *);
int size(priority_queue *);
void push(priority_queue **, int);
int top(priority_queue *);
int peek(priority_queue *);

void printArray(int array[], int n)
{
    printf("[ ");
    for (size_t i = 0; i < n; i++)
    {
        printf(" %d", array[i]);
    }
    printf(" ]\n");
};

int main()
{
    int arr[6] = {10, 2, 4, 8, 6, 9};
    priority_queue *pq = NULL;

    printf("Array: ");
    for (size_t i = 0; i < 6; i++)
    {
        printf(" %d ", arr[i]);
    }
    printf("\n");

    for (int i = 0; i < 6; i++)
    {
        push(&pq, arr[i]);
    }

    printf("Priority Queue: ");
    while (!empty(pq))
    {
        printf(" %d ", top(pq));
    }
    printf("\n");

    free(pq);
    return 0;
}

int empty(priority_queue *pq)
{
    if (pq == NULL)
    {
        return 1;
    }

    return pq->size == 0;
}

int size(priority_queue *pq)
{
    if (pq == NULL)
    {
        return 0;
    }
    return pq->size;
}

void push(priority_queue **pq, int x)
{
    if (x == 0)
    {
        printf("Queue element cannot be 0, It can be any other negative or positive integer");
        return;
    }

    if (*pq == NULL)
    {
        priority_queue *new_pq = malloc(sizeof(priority_queue));
        if (new_pq == NULL)
        {
            printf("Memory allocation failed while allocating new pririty queue");
            return;
        }

        new_pq->elements[0] = x;
        for (int i = 1; i < PRIORITY_QUEUE_MAX_SIZE; i++)
        {
            new_pq->elements[i] = 0;
        }

        new_pq->size = 1;
        *pq = new_pq;
        return;
    }

    if ((*pq)->size == PRIORITY_QUEUE_MAX_SIZE)
    {
        printf("Queue is full");
        return;
    }

    int i = 0;
    // Find the position where the new element should be inserted
    while (i < (*pq)->size && (*pq)->elements[i] >= x)
    {
        i++;
    }

    // Shift elements to the right to make space for the new element
    for (int j = (*pq)->size; j > i; j--)
    {
        (*pq)->elements[j] = (*pq)->elements[j - 1];
    }

    (*pq)->elements[i] = x;
    (*pq)->size = ((*pq)->size + 1);
}

int top(priority_queue *pq)
{
    if (pq == NULL)
    {
        return 0;
    }

    if (pq->size == 0)
    {
        return 0;
    }

    int max = pq->elements[0];
    for (int i = 0; i < PRIORITY_QUEUE_MAX_SIZE - 1; i++)
    {
        pq->elements[i] = pq->elements[i + 1];
    }
    pq->elements[PRIORITY_QUEUE_MAX_SIZE - 1] = 0;
    pq->size--;

    return max;
}

int peek(priority_queue *pq)
{
    if (pq == NULL)
    {
        return 0;
    }

    return pq->elements[0];
}
