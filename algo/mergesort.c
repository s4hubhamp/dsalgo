#include <stdio.h>
#include <stdlib.h>

int *sort(int[], int, int);
void merge(int[], int, int, int);
void print_array(int[], int);

int main()
{
    int n = 8;
    int array[] = {5, 127, 8, 5, 2, 769, 23, 346};
    printf("Original array: ");
    print_array(array, n);

    sort(array, 0, 7);

    printf("After Sorting: ");
    print_array(array, n);

    return 0;
}

int *sort(int array[], int start, int end)
{
    if (end - start == 0)
    {
        return array;
    }

    int mid = start + (int) ((end - start ) / 2);
    sort(array, start, mid);
    sort(array, mid + 1, end);
    merge(array, start, mid, end);
}

void merge(int array[], int start, int mid, int end)
{
  int start2 = mid + 1;

  // exit early
  if (array[mid] >= array[start2]) {
    return;
  }

  while (start <= mid && start2 <= end) {
    if (array[start] >= array[start2]) {
      start++;
    } else {
      int placeAtStart = array[start2];
      // shift the elements from start + 1 --> start2 - 1 to, start + 2 --> start2
      for (int i = start2; i > start; i--) {
        array[i] = array[i - 1];
      }
      array[start] = placeAtStart;

      start++;
      mid++;
      start2++;
    }
  }
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