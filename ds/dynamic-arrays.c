#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t capacity;
    size_t length;
} vector;

int vector_init(vector *vec, size_t initial_capacity);
void vector_free(vector *vec);
int vector_at(const vector *vec, size_t idx, int *value);
int vector_append(vector *vec, int n);
int vector_remove_at(vector *vec, size_t idx);
int vector_update_at(vector *vec, size_t idx, int n);
void vector_print(const vector *vec);

int main() {
    vector numbers;
    if (vector_init(&numbers, 2) != 0) {
        fprintf(stderr, "Failed to initialize vector\n");
        return 1;
    }

    vector_print(&numbers);

    vector_append(&numbers, 1);
    vector_print(&numbers);

    vector_append(&numbers, 2);
    vector_print(&numbers);

    vector_append(&numbers, 3);
    vector_print(&numbers);

    vector_remove_at(&numbers, 0);
    vector_print(&numbers);

    vector_remove_at(&numbers, 1);
    vector_print(&numbers);

    vector_remove_at(&numbers, 0);
    vector_print(&numbers);

    vector_append(&numbers, 1);
    vector_append(&numbers, 2);
    vector_append(&numbers, 3);
    vector_print(&numbers);

    vector_update_at(&numbers, 2, 1);
    vector_print(&numbers);

    int value;
    if (vector_at(&numbers, 0, &value) == 0) {
        printf("vector_at(0): %d\n", value);
    }
    if (vector_at(&numbers, 1, &value) == 0) {
        printf("vector_at(1): %d\n", value);
    }

    vector_free(&numbers);
    return 0;
}

int vector_init(vector *vec, size_t initial_capacity) {
    if (initial_capacity == 0) {
        initial_capacity = 1;
    }

    vec->elements = calloc(initial_capacity, sizeof(int));
    if (vec->elements == NULL) {
        return -1;
    }

    vec->capacity = initial_capacity;
    vec->length = 0;
    return 0;
}

void vector_free(vector *vec) {
    free(vec->elements);
    vec->elements = NULL;
    vec->capacity = 0;
    vec->length = 0;
}

static int vector_resize(vector *vec) {
    size_t new_capacity = vec->capacity * 2;
    int *new_elements = realloc(vec->elements, new_capacity * sizeof(int));
    if (new_elements == NULL) {
        return -1;
    }
    vec->elements = new_elements;
    vec->capacity = new_capacity;
    return 0;
}

int vector_at(const vector *vec, size_t idx, int *value) {
    if (idx >= vec->length) {
        return -1;
    }
    *value = vec->elements[idx];
    return 0;
}

int vector_append(vector *vec, int n) {
    if (vec->length + 1 > vec->capacity) {
        if (vector_resize(vec) != 0) {
            return -1;
        }
    }

    vec->elements[vec->length] = n;
    vec->length++;
    return 0;
}

int vector_remove_at(vector *vec, size_t idx) {
    if (idx >= vec->length) {
        return -1;
    }

    for (size_t i = idx; i < vec->length - 1; i++) {
        vec->elements[i] = vec->elements[i + 1];
    }

    vec->length--;
    return 0;
}

int vector_update_at(vector *vec, size_t idx, int n) {
    if (idx >= vec->length) {
        return -1;
    }
    vec->elements[idx] = n;
    return 0;
}

void vector_print(const vector *vec) {
    printf("\n########################\n");
    printf("    capacity %zu, length %zu\n", vec->capacity, vec->length);
    printf("    [");
    for (size_t i = 0; i < vec->length; i++) {
        printf("%s%d", i == 0 ? "" : " ", vec->elements[i]);
    }
    printf("]\n");
    printf("########################\n");
}