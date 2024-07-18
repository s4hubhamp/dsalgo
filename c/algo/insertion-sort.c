#include <stdio.h>

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void sort(int arr[], size_t len) {
    for (size_t i = 1; i < len; i++) {
      int element = arr[i];
      int j = i - 1;

      // we need to shift all elements to one place right who are
      // greter than [element]
      while (arr[j] > element && j >=0) {
        arr[j+1] = arr[j];
        j--;
      }

      arr[j+1] = element;
    }
}

int main() {
    int arr[] = {2, 7, 23, 8, 268, 2, 97, 2};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array: ");
    printArray(arr, n);
    
    sort(arr, n);
    
    printf("Sorted array: ");
    printArray(arr, n);
    
    return 0;
}

