#include <math.h>
#include <stdio.h>

int binary_search(int f, int list[], size_t len) {
  int low = 0, high = len - 1, mid;

  while (low <= high) {
    mid = (low + high) / 2;

    if (list[mid] == f) {
      return mid;
    }

    if (list[mid] < f) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  return -1;
}

int main(void) {
  int list[] = {
      1, 2, 3, 4, 5, 6,
  };

  printf("Element Index using Binary Search: %d\n", binary_search(5, list, 6));
  return 0;
}
