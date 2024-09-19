#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
    int item;
    struct list *prev;
    struct list *next;
} list;

void insert_list(list **, int);
list *search_list(list *, int);
void delete_list(list **, int);
void print_list(list *);
static list *predecessor_list(list *, int);
void reverse_list(list **);
void reverse_list_recursively(list **);
list *reverse(list *, list **);

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
    print_list(l);
    reverse_list(&l);
    print_list(l);
}

void insert_list(list **l, int x)
{
    list *head = malloc(sizeof(list));
    list *prev_head = *l;
    if (head == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    head->item = x;
    head->prev = NULL;
    head->next = prev_head;
    if (prev_head)
    {
        // when the list is empty we need to be careful to not access null ptr
        prev_head->prev = head;
    }
    *l = head;
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

    // check if the list is empty
    if (*l == NULL)
    {
        printf("List is empty, nothing to delete\n");
        return;
    }

    // check if the node is the first node inside of the list
    list *head = *l;
    if (head->item == x)
    {
        if (head->next)
        {
            head->next->prev = NULL;
        }

        *l = head->next;
        free(head);
    }
    else
    {
        list *predecessor = predecessor_list(*l, x);
        if (predecessor == NULL)
        {
            printf("Node not found inside the list\n");
        }

        list *deleted_node = predecessor->next;
        if (deleted_node->next)
        {
            deleted_node->next->prev = predecessor;
        }

        predecessor->next = deleted_node->next;
        free(deleted_node);
    }
}

static list *predecessor_list(list *l, int x)
{
    if (l == NULL || l->next == NULL)
    {
        return NULL;
    }

    if (l->next->item == x)
    {
        return l;
    }

    return predecessor_list(l->next, x);
}

void print_list(list *l)
{
    list *t = l;
    printf("\n[");

    while (t != NULL)
    {
        printf("{ item: %d, prev: %d, next: %d }", t->item, t->prev ? t->prev->item : 0, t->next ? t->next->item : 0);
        t = (list *)t->next;
    }

    printf("]\n");
}

void reverse_list(list **l)
{
    // check if the list is empty OR it has only one element
    if (*l == NULL || (*l)->next == NULL)
    {
        return;
    }

    list *prev = NULL, *curr = *l, *next_curr;
    while (curr)
    {
        next_curr = curr->next;
        curr->prev = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next_curr;
    }

    *l = prev;
}

void reverse_list_recursively(list **l)
{
    // check to see if list is empty or has only 1 element
    if (*l == NULL || (*l)->next == NULL)
    {
        return;
    }
    reverse(*l, l);
    return;
}

list *reverse(list *l, list **new_head)
{
    if (l->next == NULL)
    {
        // when we reach the last node assign it to the new head and stop the further exection of program
        *new_head = l;
        l->prev = NULL;
        l->next = NULL;
        return l;
    }

    list *reversed_list_end = reverse(l->next, new_head);
    reversed_list_end->next = l;
    l->prev = reversed_list_end;
    l->next = NULL;
    return l;
}