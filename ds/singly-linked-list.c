#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
    int item;
    struct list *next;
} list;

void insert_list(list **, int);
list *search_list(list *, int);
void delete_list(list **, int);
void print_list(list *);
static list *predecessor_list(list *, int);
void reverse_list(list **);
void reverse_list_recursively(list **);

list *head;
int main()
{
    list *l = NULL;

    insert_list(&l, 1);
    insert_list(&l, 2);
    print_list(l);

    printf("search_list(1): %p\n", search_list(l, 1));
    printf("search_list(3): %p\n", search_list(l, 3));

    delete_list(&l, 1);
    delete_list(&l, 2);
    print_list(l);

    delete_list(&l, 2);

    insert_list(&l, 1);
    insert_list(&l, 2);
    delete_list(&l, 2);
    print_list(l);
    delete_list(&l, 1);
    print_list(l);

    insert_list(&l, 1);
    insert_list(&l, 2);
    insert_list(&l, 3);
    reverse_list(&l);
    print_list(l);

    reverse_list_recursively(&l);
    print_list(l);
}

void insert_list(list **l, int item)
{
    list *p = malloc(sizeof(list));
    if (p == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    p->item = item;
    p->next = *l;
    *l = p;
}

void print_list(list *l)
{
    list *t = l;
    printf("\n[");

    while (t != NULL)
    {
        printf("%d", t->item);
        t = (list *)t->next;
    }

    printf("]\n");
}

list *search_list(list *l, int x)
{
    if (l == NULL)
    {
        return NULL;
    }

    if (l->item == x)
    {
        return l;
    }

    return search_list(l->next, x);
}

void delete_list(list **l, int x)
{
    if (*l == NULL)
    {
        printf("Empty list, Nothing to delete\n");
        return;
    }

    // check to see if first node needs to be deleted
    list *first_node = *l;
    if (first_node->item == x)
    {
        list *new_head = first_node->next;
        // free(*l);
        *l = new_head;
    }
    else
    {
        // find the predecessor node
        list *p = predecessor_list(*l, x);
        if (p == NULL)
        {
            printf("Node not found for item=%d\n", x);
            return;
        }

        list *deleted_node = p->next;
        p->next = deleted_node->next;
        free(deleted_node);
    }
}

static list *predecessor_list(list *l, int x)
{
    if (l->next == NULL)
    {
        return NULL;
    }

    if (l->next->item == x)
    {
        return l;
    }

    return predecessor_list(l->next, x);
}

void reverse_list(list **l)
{
    // check if the list is empty
    list *original_list = *l;
    if (*l == NULL || original_list->next == NULL)
    {
        return;
    }

    list *curr = *l, *prev = NULL;

    while (curr)
    {
        list *next_curr = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next_curr;
    }

    *l = prev;
}

void reverse_list_recursively(list **l)
{
    // Base case: if the list is empty or has only one element
    if (*l == NULL || (*l)->next == NULL)
    {
        return;
    }

    // Store the second element (which will be the last after reversal)
    list *rest = (*l)->next;

    // Recursive call on the rest of the list
    reverse_list_recursively(&rest);

    // Reverse the connection
    (*l)->next->next = *l;
    (*l)->next = NULL;

    // Update the head to the last element (which is now the first)
    *l = rest;
}
