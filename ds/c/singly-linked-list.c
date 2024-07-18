#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int val;
  struct list *next;
} list;

void insert_list(list **, int);
void print_list(list *);

/**
implement array using structs which includes additional handy props
such as length, slice, split, concat etc
 */
int main(void) {
  int numbers[] = {1, 2, 3, 4, 5};
  int len = sizeof(numbers) / sizeof(numbers[0]);
  list *l = NULL;
  for (int i = 0; i < len; i++) {
    insert_list(&l, numbers[i]);
  }
  print_list(l);
  return 1;
}

// insert at the start of the list
void insert_list(list **l, int val) {
  list *head = malloc(sizeof(list));
  head->val = val;
  head->next = *l;
  *l = head;
}

void print_list(list *l) {
  list *curr = l;
  printf("\n");
  while (curr) {
    printf(" %d", curr->val);
    curr = curr->next;
  }
}