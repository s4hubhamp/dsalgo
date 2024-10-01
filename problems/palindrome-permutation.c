// Palindrome Permutation: Given a string, write a function to check if it is a permutation of a palin
// drome. A palindrome is a word or phrase that is the same forwards and backwards. A permutation
// is a rearrangement of letters. The palindrome does not need to be limited to just dictionary words.

#include <stdio.h>

void print_array(int array[], int n)
{
    printf("[ ");
    for (size_t i = 0; i < n; i++)
    {
        printf(" %d", array[i]);
    }
    printf(" ]\n");
};

int is_palindrome_permutation(char *s)
{
    // we need to check the number of unique characters inside of string
    int table[26 * 2] = {0};
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] >= 'a')
        {
            table[s[i] - 'A' - 6]++;
        }
        else
        {
            table[s[i] - 'A']++;
        }
        i++;
    }

    print_array(table, 26 * 2);

    int found_odd = 0;
    for (int j = 0; j < 26 * 2; j++)
    {
        if (table[j] % 2 != 0)
        {
            if (found_odd)
            {
                return 0;
            }
            found_odd = 1;
        }
    }

    return 1;
}

int main()
{
    char *s = "aabcb";
    printf("is_palindrome_permutation(%s): %d\n", s, is_palindrome_permutation(s));
}
