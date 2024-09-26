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
void bubble_up(priority_queue *, int);
void bubble_down(priority_queue *, int);

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

// check if the position of curr is in correct order if not we need to replace curr and his parent
void bubble_up(priority_queue *pq, int curr)
{
    int p = parent(curr);
    if (p == -1)
    {
        return;
    }

    if (pq->elements[curr] > pq->elements[p])
    {
        swap(pq->elements, curr, p);
        bubble_up(pq, p);
    }
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

    // we need to check if the newer inserted element is at correct position(by comparing it with it's parent)
    // if not the element gets bubbled up
    bubble_up(*pq, (*pq)->size);
}

void bubble_down(priority_queue *pq, int curr)
{
    if (curr == pq->size)
    {
        return;
    }

    int l = left(curr);
    int r = right(curr);
    int larger_down_idx = -1;
    if (l <= pq->size && r <= pq->size)
    {
        larger_down_idx = pq->elements[l] > pq->elements[r] ? l : r;
    }
    else if (l <= pq->size)
    {
        larger_down_idx = l;
    }
    else if (r <= pq->size)
    {
        larger_down_idx = r;
    }

    if (larger_down_idx == -1 || pq->elements[larger_down_idx] < pq->elements[curr])
    {
        return;
    }

    swap(pq->elements, larger_down_idx, curr);
    bubble_down(pq, larger_down_idx);
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

    // new root will get bubbled down until it goes into correct position
    bubble_down(pq, 1);

    return return_val;
}
