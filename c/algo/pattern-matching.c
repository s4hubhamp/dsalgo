#include<stdio.h>
#include<string.h>

int find_index(char *t, char *p) {
    for (size_t i = 0; i < strlen(t); i++) {
        int found = 1;
        for(size_t j = 0; j < strlen(p); j++) {
            size_t curr = i + j;
            if (curr > strlen(t) || t[curr] != p[j]) {
                found = 0;
                break;
            }
        }

        if (found) {
            return i;
        }
    }

    return -1;
}

int main() {
    char *t = "aababba";
    char *p = "abba";

    int idx = find_index(t, p);
    printf("Substring index: %d\n", idx);

    return 0;
}