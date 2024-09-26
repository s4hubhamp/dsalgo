// here we use an optimized heapify function to create heap
// to see first version of inserting elements into heap refer to ds/heap*

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_QUEUE_SIZE 5

typedef struct priority_queue
{
    int elements[MAX_QUEUE_SIZE + 1];
    int size;
} priority_queue;

void insert(priority_queue **, int);
int pop(priority_queue *);
void bubble_down(priority_queue *, int);
void sort(int[], int);
void swap(int elements[], int i, int j)
{
    int temp = elements[i];
    elements[i] = elements[j];
    elements[j] = temp;
}
void print_array(int array[], int n)
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
    int a[] = {1, 2, 3, 4, 5};
    sort(a, 5);
    printf("Sorted Array: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}

void sort(int arr[], int n)
{
    // create a queue
    priority_queue *pq = malloc(sizeof(priority_queue));
    if (pq == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    pq->size = 0;

    // copy array elements inside the queue
    if (n > MAX_QUEUE_SIZE)
    {
        printf("Only %d elements can be sorted\n", MAX_QUEUE_SIZE);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        pq->elements[++pq->size] = arr[i];
    }

    // heapify from floor(pq->size/2)(last parent) to 1 until we restore dominance order
    for (int parent_index = (int)(pq->size / 2); parent_index >= 1; parent_index--)
    {
        bubble_down(pq, parent_index);
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = pop(pq);
    }
}

void bubble_down(priority_queue *pq, int parent_index)
{
    // we need to check whether element at parent_index is actually in a valid spot
    int big_child_index = -1;
    int left_child_index = 2 * parent_index;
    int right_child_index = 2 * parent_index + 1;
    if ((left_child_index <= pq->size) && (right_child_index <= pq->size))
    {
        big_child_index = pq->elements[left_child_index] > pq->elements[right_child_index]
                              ? left_child_index
                              : right_child_index;
    }
    else if (left_child_index <= pq->size)
    {
        big_child_index = left_child_index;
    }
    else if (right_child_index <= pq->size)
    {
        big_child_index = right_child_index;
    }

    if (big_child_index == -1)
    {
        return;
    }

    if (pq->elements[big_child_index] > pq->elements[parent_index])
    {

        swap(pq->elements, parent_index, big_child_index);
        bubble_down(pq, big_child_index);
    }
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
