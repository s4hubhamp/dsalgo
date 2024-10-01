// URLify: Write a method to replace all spaces in a string with '%20'. You may assume that the string
// has sufficient space at the end to hold the additional characters,and that you are given the "true"
// length of the string. (Note: If implementing in Java, please use a character array so that you can
// perform this operation in place.)

#include <stdio.h>

void urlify(char *s, int true_length)
{
    int spaces = 0;

    for (int i = 0; i < true_length; i++)
    {
        if (s[i] == ' ')
        {
            spaces++;
        }
    }

    int len = true_length + spaces * 2;
    s[len] = '\0';

    for (int j = true_length - 1; j >= 0; j--)
    {
        if (s[j] != ' ')
        {
            s[--len] = s[j]; // Move characters back
        }
        else
        {
            s[--len] = '0';
            s[--len] = '2';
            s[--len] = '%';
        }
    }
}

int main()
{
    char s[] = "Mr John Smith    ";
    int tl = 13;
    printf("original: '%s'\n", s);
    urlify(s, tl);
    printf("after: '%s'\n", s);
    return 0;
}
