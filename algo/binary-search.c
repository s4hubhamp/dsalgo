#include <stdio.h>

int binary_search(int s[], int key, int low, int high)
{
    int middle; /* index of middle element */
    if (low > high)
        return (-1); /* key not found */
    middle = (low + high) / 2;
    if (s[middle] == key)
        return (middle);
    if (s[middle] > key)
        return (binary_search(s, key, low, middle - 1));
    else
        return (binary_search(s, key, middle + 1, high));
}

int main()
{
    int nums[] = {10, 20, 30, 40, 50, 60};
    int idx = binary_search(nums, 60, 0, 5);
    printf("Index is: %d\n", idx);
    return 0;
}