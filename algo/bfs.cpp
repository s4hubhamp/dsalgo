#include <iostream>
#include <queue>

using namespace std;

typedef struct tree
{
    int value;
    struct tree *parent;
    struct tree *left;
    struct tree *right;
} tree;

tree *create_node(int val)
{
    tree *node = (tree *)malloc(sizeof(tree));
    node->value = val;
    return node;
}

void bfs_traverse(tree *root)
{
    queue<tree *> q;
    q.push(root);

    while (!q.empty())
    {
        tree *curr = q.front();
        if (curr)
        {
            cout << curr->value << " ";
            q.push(curr->left);
            q.push(curr->right);
        }
        q.pop();
    }
    cout << endl;
}

int main()
{
    tree *root = create_node(1);
    root->left = create_node(2);
    root->right = create_node(3);

    root->left->left = create_node(4);
    root->left->right = create_node(5);

    bfs_traverse(root);

    return 0;
}
