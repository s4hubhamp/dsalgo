// Given a string t find start idx of the pattern p inside t

#include <stdio.h>
#include <string.h>

int find(char *, char *);

int main()
{
    printf("pattern found at: %d\n", find("abba", "aababba"));
    return 0;
}

int find(char *p, char *t)
{
    int n = strlen(t);
    int m = strlen(p);

    for (int i = 0; i <= n - m; i++)
    {
        int j = 0; /* pointer to the current position in p */
        while (t[j + i] == p[j] && j < m)
        {
            j++;
        }

        if (j == m)
        {
            return i;
        }
    }

    return -1;
}
