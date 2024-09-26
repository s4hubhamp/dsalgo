#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define HEAP_MAX_SIZE 4

typedef struct priority_queue
{
    int elements[HEAP_MAX_SIZE + 1]; // zero'th index is kept empty to simplify index calculations
    int size;                        // because 0'th index is empty the size actually represents last occupied index
} priority_queue;

void insert(priority_queue **, int);
int pop(priority_queue *);
int parent(int i)
{
    if (i == 1)
    {
        return -1;
    }
    return (int)(i / 2); // implicit floor
}
int left(int i)
{
    return 2 * i;
}
int right(int i)
{
    return (2 * i) + 1;
}
void swap(int elements[], int i, int j)
{
    int temp = elements[i];
    elements[i] = elements[j];
    elements[j] = temp;
}
int main()
{
    priority_queue *pq = NULL;

    insert(&pq, 4);
    insert(&pq, 8);
    insert(&pq, 9);
    insert(&pq, 1000);

    printf("Max values: ");
    int x;
    while ((x = pop(pq)) != INT_MIN)
    {
        printf(" %d ", x);
    }
    printf("\n");

    return 0;
}

void insert(priority_queue **pq, int x)
{
    if (*pq == NULL)
    {
        *pq = malloc(sizeof(priority_queue));
        if (*pq == NULL)
        {
            printf("Memory allocation failed");
            return;
        }

        (*pq)->size = 1;
        (*pq)->elements[(*pq)->size] = x;
        return;
    }

    if ((*pq)->size == HEAP_MAX_SIZE)
    {
        printf("HEAP_MAX_SIZE reached");
        return;
    }

    // step 1: insert will happen at the end of the array
    (*pq)->elements[++(*pq)->size] = x;

    // printf("Inserted new element at position: %d element in array: %d\n", (*pq)->size, (*pq)->elements[(*pq)->size]);

    // we need to check if the newer inserted element is at correct position(by comparing it with parent)
    // if not swap it with parent
    int i = (*pq)->size;
    int p = parent(i);

    while ((p != -1) && ((*pq)->elements[p] < (*pq)->elements[i]))
    {
        // printf("I: %d and p: %d (*pq)->elements[p]: %d (*pq)->elements[i]: %d\n",
        //        i, p, (*pq)->elements[p], (*pq)->elements[i]);
        swap((*pq)->elements, i, p);
        // printf("After swapping (*pq)->elements[p]: %d (*pq)->elements[i]: %d\n",
        //        (*pq)->elements[p], (*pq)->elements[i]);

        i = p;
        p = parent(i);
    }

    // printf("Result Size: %d Values inside of the array: %d %d\n", (*pq)->size, (*pq)->elements[1], (*pq)->elements[2]);
}

int pop(priority_queue *pq)
{
    if (pq == NULL || !pq->size)
    {
        return INT_MIN;
    }

    int return_val = pq->elements[1];

    // put the rightmost leaf on end level at the root position
    pq->elements[1] = pq->elements[pq->size];
    pq->size--;

    // compare new root with it's children against heap's property
    // continue to swap items until we correct the entire heap
    int i = 1;
    int l = left(i);
    int r = right(i);
    while ((l <= pq->size && pq->elements[i] < pq->elements[l]) ||
           (r <= pq->size && pq->elements[i] < pq->elements[r]))
    {
        int swap_target = (l <= pq->size && pq->elements[i] < pq->elements[l]) ? l : r;
        swap(pq->elements, i, swap_target);
        i = (swap_target == l) ? l : r;
        l = left(i);
        r = right(i);
    }

    return return_val;
}
