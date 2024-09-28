// the largest element bubbles to the end

#include <stdio.h>

void sort(int[], int);
void swap(int[], int, int);
void printArray(int[], int);

int main()
{
    int array[10] = {6, 2, 3, 4, 5};
    printf("Unsorted array: ");
    printArray(array, 5);
    sort(array, 5);
    printf("Sorted array: ");
    printArray(array, 5);
    return 0;
}

void sort(int array[], int n)
{
    for (size_t i = 0; i < n; i++)
    {
        int swapped = 0;
        for (size_t j = 1; j < n - i; j++)
        {
            if (array[j - 1] > array[j])
            {
                swap(array, j - 1, j);
                swapped = 1;
            }
        }

        if (!swapped)
        {
            break;
        }
    }
}

void swap(int array[], int i, int j)
{
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void printArray(int array[], int n)
{
    printf("[ ");
    for (size_t i = 0; i < n; i++)
    {
        printf(" %d", array[i]);
    }
    printf(" ]\n");
};