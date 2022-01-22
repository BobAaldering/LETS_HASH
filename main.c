#include <stdio.h>

#include "hash.h"

int main() {
    const char* str = "Do you want a hash?";

    printf("Hashed value: %u", hash_fnv_string(str));

    return 0;
}
