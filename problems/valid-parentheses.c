#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_valid(char *s)
{
    // we will implement stack as a singly linked list where top is always the root node
    // removal is easy and insert is also easy
    typedef struct Stack
    {
        char p;
        struct Stack *next;
    } Stack;

    Stack *t = NULL;
    int i = 0;
    char c;
    while ((c = s[i]) != '\0')
    {
        printf("c: %c t->p: %c\n", c, t ? t->p : NULL);
        if (c == '(' || c == '[' || c == '{')
        {
            printf("Inside if block\n");
            Stack *new_node = malloc(sizeof(Stack));
            new_node->p = c;
            new_node->next = t;
            t = new_node;
        }
        else
        {
            printf("Inside else block\n");
            // case 1: trying to remove from empty stack
            if (t == NULL)
            {
                return false;
            }

            // case 2: removed paranthesis does not match the respective opening paranthesis
            if ((c == ')' && t->p != '(') || (c == ']' && t->p != '[') || (c == '}' && t->p != '{'))
            {
                return false;
            }

            // top becomes new
            t = t->next;
        }
        i++;
    }

    // case 3: if stack is non empty
    if (t != NULL)
    {
        return false;
    }

    return true;
}

int main()
{
    char *test1 = "()()";
    char *test2 = "()(";
    char *test3 = "(";
    char *test4 = "([{}]())[]";
    char *test5 = "[(({})}]";

    // printf("test1: %d\n", is_valid(test1));
    // printf("test2: %d\n", is_valid(test2));
    // printf("test3: %d\n", is_valid(test3));
    // printf("test4: %d\n", is_valid(test4));
    printf("test5: %d\n", is_valid(test5));
}