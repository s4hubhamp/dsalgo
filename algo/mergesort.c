#include <stdio.h>
#include <stdlib.h>

int *sort(int[], int);
int *slice(int array[], int start, int end);
int *merge(int a[], int na, int b[], int nb);
void print_array(int[], int);

int main()
{
    int n = 8;
    int array[] = {5, 127, 8, 5, 2, 769, 23, 346};
    printf("Original array: ");
    print_array(array, n);

    int *sorted = sort(array, n);

    printf("Sorted array: ");
    print_array(sorted, n);

    return 0;
}

int *sort(int array[], int n)
{
    if (n == 1)
    {
        return array;
    }

    int lefthalf[] = {0, (int)(n / 2)};
    int righthalf[] = {(int)(n / 2), n};

    int *sortedleft = sort(slice(array, lefthalf[0], lefthalf[1]), lefthalf[1] - lefthalf[0]);
    int *sortedright = sort(slice(array, righthalf[0], righthalf[1]), righthalf[1] - righthalf[0]);

    return sortedright[0] > sortedleft[0]
               ? merge(sortedright, righthalf[1] - righthalf[0], sortedleft, lefthalf[1] - lefthalf[0])
               : merge(sortedleft, lefthalf[1] - lefthalf[0], sortedright, righthalf[1] - righthalf[0]);
}

int *merge(int a[], int na, int b[], int nb)
{
    int *result = malloc(sizeof(int) * (na + nb));
    int i = 0, j = 0, k = 0;

    while (i < na && j < nb)
    {
        if (a[i] > b[j])
        {
            result[k++] = a[i++];
        }
        else
        {
            result[k++] = b[j++];
        }
    }

    while (i < na)
        result[k++] = a[i++];
    while (j < nb)
        result[k++] = b[j++];

    return result;
}

int *slice(int array[], int start, int end)
{
    int *sliced_arr = malloc(sizeof(int) * (end - start));
    int j = -1;
    for (int i = start; i < end; i++)
    {
        sliced_arr[++j] = array[i];
    }

    return sliced_arr;
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