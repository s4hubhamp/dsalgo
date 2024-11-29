#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _HASH_TABLE_SIZE_ 1000

typedef struct List
{
    int key;
    int value;
    struct List *prev;
    struct List *next;
} List;

typedef struct LRUCache
{
    int capacity;
    int size;
    // to handle keys collisions we want to group the colliding keys hence the table element is array of ListNodes
    List *hash_table[_HASH_TABLE_SIZE_];
    List *head;
    List *tail;
} LRUCache;

LRUCache *lRUCacheCreate(int capacity)
{
    LRUCache *cache = malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;
    // fill the table with zeros
    memset(cache->hash_table, 0, sizeof(cache->hash_table));
    return cache;
}

size_t get_hash(int x)
{
    return x % _HASH_TABLE_SIZE_;
}

List *find_node_by_key(LRUCache *cache, int key)
{
    size_t hash = get_hash(key);
    List *curr = cache->hash_table[hash];
    while (curr)
    {
        if (curr->key == key)
        {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

// the most recently accessed node will be set as the new head
void promote_node(LRUCache *cache, List *node)
{
    if (node == cache->head)
    {
        return;
    }
    if (node == cache->tail)
    {
        cache->tail = node->prev;
    }
    if (node->prev)
    {
        node->prev->next = node->next;
    }
    if (node->next)
    {
        node->next->prev = node->prev;
    }
    node->prev = NULL;
    node->next = cache->head;
    if (cache->head)
    {
        cache->head->prev = node;
    }
    cache->head = node;
}

int lRUCacheGet(LRUCache *cache, int key)
{
    List *node = find_node_by_key(cache, key);

    if (node)
    {
        promote_node(cache, node);
        return cache->head->value;
    }

    return -1;
}

void lRUCachePut(LRUCache *cache, int key, int value)
{
    // first thing is to find the node
    List *node = find_node_by_key(cache, key);

    // if node exists then we should update the value and make it as new head
    if (node)
    {
        node->value = value;
        promote_node(cache, node);
    }
    else
    {
        // evict the last node if necessary
        if (cache->size == cache->capacity)
        {
            List *prev_tail = cache->tail;
            cache->tail = cache->tail->prev;
            if (cache->tail)
            {
                cache->tail->next = NULL;
            }
            else
            {
                cache->head = NULL;
            }
            free(prev_tail);
            cache->size--;
        }

        // put the new node at start of the list
        List *new_node = malloc(sizeof(List));
        new_node->key = key;
        new_node->value = value;
        new_node->prev = NULL;
        new_node->next = cache->head;
        if (cache->head)
        {
            cache->head->prev = new_node;
        }
        cache->head = new_node;
        if (cache->tail == NULL)
        {
            cache->tail = new_node;
        }
        cache->size++;
    }
}

void lRUCacheFree(LRUCache *cache)
{
    // Free all the nodes in the list
    List *current = cache->head;
    while (current)
    {
        List *next = current->next;
        free(current);
        current = next;
    }

    // Free the cache itself
    free(cache);
}

int main()
{
    LRUCache *obj = lRUCacheCreate(2);

    // printf("1. obj->head: %p obj->head->prev: %p obj->tail: %p obj->tail->next: %p\n", obj->head, obj->head ? obj->head->prev : NULL, obj->tail, obj->tail ? obj->tail->next : NULL);
    lRUCachePut(obj, 1, 1);
    // printf("2. obj->head: %p obj->head->prev: %p obj->tail: %p obj->tail->next: %p\n", obj->head, obj->head ? obj->head->prev : NULL, obj->tail, obj->tail ? obj->tail->next : NULL);
    lRUCachePut(obj, 2, 2);
    // printf("3 obj->head: %p obj->head->prev: %p obj->tail: %p obj->tail->next: %p\n", obj->head, obj->head ? obj->head->prev : NULL, obj->tail, obj->tail ? obj->tail->next : NULL);
    printf("lRUCacheGet(obj, 1): %d\n", lRUCacheGet(obj, 1));
    // printf("4 obj->head: %p obj->head->prev: %p obj->tail: %p obj->tail->next: %p\n", obj->head, obj->head ? obj->head->prev : NULL, obj->tail, obj->tail ? obj->tail->next : NULL);
    lRUCachePut(obj, 3, 3);
    // printf("5 obj->head: %p obj->head->prev: %p obj->tail: %p obj->tail->next: %p\n", obj->head, obj->head ? obj->head->prev : NULL, obj->tail, obj->tail ? obj->tail->next : NULL);
    printf("lRUCacheGet(obj, 2): %d\n", lRUCacheGet(obj, 2));
    // printf("6 obj->head: %p obj->head->prev: %p obj->tail: %p obj->tail->next: %p\n", obj->head, obj->head ? obj->head->prev : NULL, obj->tail, obj->tail ? obj->tail->next : NULL);
    lRUCachePut(obj, 4, 4);
    // printf("7 obj->head: %p obj->head->prev: %p obj->tail: %p obj->tail->next: %p\n", obj->head, obj->head ? obj->head->prev : NULL, obj->tail, obj->tail ? obj->tail->next : NULL);
    printf("lRUCacheGet(obj, 1): %d\n", lRUCacheGet(obj, 1));
    // printf("8 obj->head: %p obj->head->prev: %p obj->tail: %p obj->tail->next: %p\n", obj->head, obj->head ? obj->head->prev : NULL, obj->tail, obj->tail ? obj->tail->next : NULL);
    printf("lRUCacheGet(obj, 3): %d\n", lRUCacheGet(obj, 3));
    // printf("9 obj->head: %p obj->head->prev: %p obj->tail: %p obj->tail->next: %p\n", obj->head, obj->head ? obj->head->prev : NULL, obj->tail, obj->tail ? obj->tail->next : NULL);
    printf("lRUCacheGet(obj, 4): %d\n", lRUCacheGet(obj, 4));
    // printf("10 obj->head: %p obj->head->prev: %p obj->tail: %p obj->tail->next: %p\n", obj->head, obj->head ? obj->head->prev : NULL, obj->tail, obj->tail ? obj->tail->next : NULL);

    printList(obj->head);

    lRUCacheFree(obj);
}