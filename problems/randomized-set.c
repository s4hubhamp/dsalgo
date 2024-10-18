#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TABLE_SIZE 100
#define DYNAMIC_ARRAY_INITIAL_CAP 4

typedef struct DArray
{
    int *elements;
    size_t capacity;
    size_t size;
} DArray;

typedef struct
{
    DArray *hash_table[TABLE_SIZE];
} RandomizedSet;

void icrease_darray_cap(DArray *da)
{
    // increase capacity by two times
    da->capacity *= 2;
    da->elements = realloc(da->elements, sizeof(int) * da->capacity);
}

DArray *create_darray()
{
    DArray *da = malloc(sizeof(DArray));
    da->size = 0;
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAP;
    da->elements = malloc(sizeof(int) * da->capacity);
    return da;
}

RandomizedSet *randomizedSetCreate()
{
    RandomizedSet *set = malloc(sizeof(RandomizedSet));
    int i = 0;
    while (i < TABLE_SIZE)
    {
        set->hash_table[i] = create_darray();
        i++;
    }
    return set;
}

int hash(int x) { return ((x % TABLE_SIZE) + TABLE_SIZE) % TABLE_SIZE; }

int searchBucket(DArray *bucket, int val)
{

    // search for value inside the bucket
    for (size_t i = 0; i < bucket->size; i++)
    {
        if (bucket->elements[i] == val)
        {
            return i;
        }
    }

    return -1;
}

bool randomizedSetInsert(RandomizedSet *set, int val)
{
    int h = hash(val);
    DArray *bucket = set->hash_table[h];
    int idx = searchBucket(bucket, val);
    if (idx > -1)
    {
        return false;
    }

    if (bucket->size == bucket->capacity)
    {
        icrease_darray_cap(bucket);
    }

    bucket->elements[bucket->size++] = val;
    return true;
}

bool randomizedSetRemove(RandomizedSet *set, int val)
{
    int h = hash(val);
    DArray *bucket = set->hash_table[h];
    int idx = searchBucket(bucket, val);
    if (idx == -1)
    {
        return false;
    }

    // move the last element to the deleted index
    bucket->elements[idx] = bucket->elements[--bucket->size];

    // TODO: We can reduce a bucket size here
    return true;
}

int randomizedSetGetRandom(RandomizedSet *set)
{
    static bool seeded = false;
    if (!seeded)
    {
        srand((unsigned int)time(NULL));
        seeded = true;
    }

    // Select a non-empty bucket
    DArray *bucket;
    do
    {
        bucket = set->hash_table[rand() % TABLE_SIZE];
    } while (bucket->size == 0);

    return bucket->elements[rand() % bucket->size];
}

void randomizedSetFree(RandomizedSet *set)
{
    size_t totalSize = sizeof(RandomizedSet);

    for (size_t i = 0; i < TABLE_SIZE; i++)
    {
        // Size of each DArray structure
        totalSize += sizeof(DArray);
        // Size of elements array in each DArray
        totalSize += set->hash_table[i]->capacity * sizeof(int);

        free(set->hash_table[i]->elements);
        free(set->hash_table[i]);
    }

    free(set);
    // printf("freed: %zu bytes\n", totalSize);
}
