#include <stdio.h>
#include <stdlib.h>

void quicksort(int[], int low, int high);
int partition(int[], int low, int high);
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
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
    int n = 5;
    int array[] = {10, 80, 90, 20, 70};
    printf("Original array: ");
    print_array(array, n);

    quicksort(array, 0, n - 1);
    printf("After Sorting: ");
    print_array(array, n);
}

void quicksort(int s[], int low, int high)
{
    // Base case: If the array has one or no elements, it's already sorted
    if (low >= high)
    {
        return;
    }

    // Partition the array and get the index of the pivot element
    int pivot = partition(s, low, high);

    // Recursively sort the elements before and after the pivot
    quicksort(s, low, pivot - 1);
    quicksort(s, pivot + 1, high);
}

// Function to partition the array into two halves
// It picks the last element as pivot and arranges all smaller elements to the left
// and larger elements to the right of the pivot, then returns the pivot's final position
int partition(int s[], int low, int high)
{
    int i = low - 1;     // Index of last smaller element than pivot
    int pivot = s[high]; // Pivot is chosen as the last element in the current subarray

    for (int j = low; j < high; j++)
    {
        // If the current element is smaller than the pivot move the current element to the left side
        if (s[j] < pivot)
        {
            i++;
            swap(&s[i], &s[j]);
        }
    }

    // put the Pivot at the correct position
    swap(&s[high], &s[i + 1]);
    return i + 1;
}