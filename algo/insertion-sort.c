// Iterate over each element in array and insert the element in sorted array

#include <stdio.h>

void sort(int[], int);
void swap(int[], int, int);
void printArray(int[], int);

int main()
{
    int array[10] = {5, 127, 8, 5, 2, 769, 23, 346, 8, 3};
    sort(array, 10);
    printArray(array, 10);
    return 0;
}

void sort(int array[], int n)
{
    for (size_t i = 1; i < n; i++)
    {
        size_t j = i;
        while (j > 0 && array[j] < array[j - 1])
        {
            swap(array, j, j - 1);
            j--;
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