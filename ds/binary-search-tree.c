#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tree
{
    int value;
    struct tree *parent;
    struct tree *left;
    struct tree *right;
} tree;

typedef enum traversal_type
{
    IN_ORDER,
    PRE_ORDER,
    POST_ORDER,
    LEVEL_ORDER
} traversal_type;

tree *search_tree(tree *l, int x);
tree *find_minimum(tree *t);
tree *find_maximum(tree *t);
void traverse_tree(tree *l, traversal_type type);
tree *insert_tree(tree **l, int x, tree *parent);
int max_depth(tree *);
void process_current_level(tree *, int);
void delete_tree(tree **t, tree *d);
bool is_valid_bst(tree *t, tree *p);

int main()
{
    tree *t = NULL;

    insert_tree(&t, 40, NULL);
    tree *p = insert_tree(&t, 30, t);
    insert_tree(&t, 25, p);
    insert_tree(&t, 35, p);
    tree *q = insert_tree(&t, 50, t);
    insert_tree(&t, 45, q);
    insert_tree(&t, 60, q);

    printf("search_tree(t, 40): %p\n", search_tree(t, 40));
    printf("search_tree(t, 60): %p\n", search_tree(t, 60));
    printf("search_tree(t, 20): %p\n", search_tree(t, 20));

    printf("minimum: %d\n", find_minimum(t)->value);
    printf("maximum: %d\n", find_maximum(t)->value);

    printf("traverse_tree(IN_ORDER): ");
    traverse_tree(t, IN_ORDER);
    printf("\n");

    printf("traverse_tree(PRE_ORDER): ");
    traverse_tree(t, PRE_ORDER);
    printf("\n");

    printf("traverse_tree(POST_ORDER): ");
    traverse_tree(t, POST_ORDER);
    printf("\n");

    printf("traverse_tree(LEVEL_ORDER): ");
    traverse_tree(t, LEVEL_ORDER);
    printf("\n");

    delete_tree(&t, search_tree(t, 60));
    printf("is_valid_bst ? %d\n", is_valid_bst(t, NULL));
    printf("traverse_tree(LEVEL_ORDER): ");
    traverse_tree(t, LEVEL_ORDER);
    printf("\n");

    delete_tree(&t, search_tree(t, 50));
    printf("is_valid_bst ? %d\n", is_valid_bst(t, NULL));
    printf("traverse_tree(LEVEL_ORDER): ");
    traverse_tree(t, LEVEL_ORDER);
    printf("\n");

    delete_tree(&t, search_tree(t, 30));
    printf("is_valid_bst ? %d\n", is_valid_bst(t, NULL));
    printf("traverse_tree(LEVEL_ORDER): ");
    traverse_tree(t, LEVEL_ORDER);
    printf("\n");

    delete_tree(&t, t);
    printf("is_valid_bst ? %d\n", is_valid_bst(t, NULL));
    printf("traverse_tree(LEVEL_ORDER): ");
    traverse_tree(t, LEVEL_ORDER);
    printf("\n");

    return 0;
}

tree *insert_tree(tree **l, int x, tree *parent)
{
    if (*l == NULL)
    {
        tree *t = malloc(sizeof(tree));
        t->value = x;
        t->left = NULL;
        t->right = NULL;
        t->parent = parent;
        *l = t;
        return t;
    }

    if (x < (*l)->value)
    {
        return insert_tree(&(*l)->left, x, parent);
    }

    return insert_tree(&(*l)->right, x, parent);
}

tree *search_tree(tree *l, int x)
{
    if (l == NULL)
    {
        return l;
    }

    if (l->value == x)
    {
        return l;
    }

    if (x < l->value)
    {
        return search_tree(l->left, x);
    }

    return search_tree(l->right, x);
}

tree *find_minimum(tree *t)
{
    if (t == NULL || t->left == NULL)
    {
        return t;
    }

    return find_minimum(t->left);
}

tree *find_maximum(tree *t)
{
    if (t == NULL || t->right == NULL)
    {
        return t;
    }

    return find_maximum(t->right);
}

void traverse_tree(tree *t, traversal_type type)
{
    if (t == NULL)
    {
        return;
    }

    if (type == IN_ORDER)
    {
        traverse_tree(t->left, type);
        printf(" %d ", t->value);
        traverse_tree(t->right, type);
    }
    else if (type == PRE_ORDER)
    {
        printf(" %d ", t->value);
        traverse_tree(t->left, type);
        traverse_tree(t->right, type);
    }
    else if (type == POST_ORDER)
    {
        traverse_tree(t->left, type);
        traverse_tree(t->right, type);
        printf(" %d ", t->value);
    }
    else
    {
        int d = max_depth(t);

        for (int i = 1; i <= d; i++)
        {
            process_current_level(t, i);
            printf("\n");
        }
    }
}

void process_current_level(tree *t, int l)
{
    if (t == NULL)
    {
        return;
    }

    if (l == 1)
    {
        printf(" [value: %d, address: %p, parent: %p] ", t->value, t, t->parent);
    }

    if (l > 1)
    {
        process_current_level(t->left, l - 1);
        process_current_level(t->right, l - 1);
    }
}

int max_depth(tree *t)
{
    if (t == NULL)
    {
        return 0;
    }

    int ldepth = max_depth(t->left);
    int rdepth = max_depth(t->right);
    return (ldepth > rdepth ? ldepth : rdepth) + 1;
}

void delete_tree(tree **t, tree *d)
{
    if (t == NULL || d == NULL)
    {
        return;
    }

    // case 1: if node to be deleted is leaf node
    if (d->left == NULL && d->right == NULL)
    {
        if (d->parent != NULL)
        {
            if (d->parent->left == d)
            {
                d->parent->left = NULL;
            }
            else
            {
                d->parent->right = NULL;
            }
        }
        else
        {
            // root node
            *t = NULL;
        }
        free(d);
    }
    // case 2: node to be deleted has only one child
    else if (d->left == NULL || d->right == NULL)
    {

        tree *grand_child = d->left == NULL ? d->right : d->left;
        if (d->parent != NULL)
        {
            // know whether the deleted node is at right side or left side of parent
            if (d->parent->left == d)
            {
                d->parent->left = grand_child;
            }
            else
            {
                d->parent->right = grand_child;
            }
        }
        else
        {
            // root node
            *t = grand_child;
        }

        grand_child->parent = d->parent;
        free(d);
    }
    else
    {
        // this is the case where d has two children. Here we need to put leftmost node in right subtree
        // in place of d so that property of BST holds
        tree *successor = find_minimum(d->right);
        int successor_value = successor->value;
        delete_tree(t, successor);
        d->value = successor_value;
    }
}

bool is_valid_bst(tree *t, tree *p)
{
    if (t == NULL)
    {
        return true;
    }

    if (t->parent != p && p != NULL)
    {
        return false;
    }

    if (t->left != NULL)
    {
        if (t->left->value <= t->value)
        {
            return is_valid_bst(t->left, t);
        }
        return false;
    }

    if (t->right != NULL)
    {
        if (t->right->value > t->value)
        {
            return is_valid_bst(t->right, t);
        }
        return false;
    }

    return true;
}