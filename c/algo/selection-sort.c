#include <stdio.h>

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void sort(int arr[], size_t len) {
    for (size_t i = 0; i < len; i++) {
        int min = i;
        for (size_t j = i+1; j < len; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        // swap the i and min
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
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
