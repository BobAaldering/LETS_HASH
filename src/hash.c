#include "hash.h"

#if HASH_BITS == 32
    #define DJB2_OFFSET (0x00001505)

    #define FNV_PRIME (0x01000193)
    #define FNV_OFFSET_BASIS (0x811c9dc5)
#elif HASH_BITS == 64
    #define DJB2_OFFSET (0x0000000000001505)

    #define FNV_PRIME (0x00000100000001B3)
    #define FNV_OFFSET_BASIS (0xcbf29ce484222325)
#endif

__attribute__((unused)) int get_hash_bits() {
    return HASH_BITS;
}

__attribute__((unused)) hash_value_t hash_djb2_generic(const void *data, size_t size_data) {
    const unsigned char* data_single_byte = data;
    hash_value_t hash_value = DJB2_OFFSET;

    while (size_data--) {
        hash_value = ((hash_value << 5) + hash_value) + *data_single_byte++;
        data_single_byte++;
    }

    return hash_value;
}

__attribute__((unused)) hash_value_t hash_djb2_string(const char used_string[static 1]) {
    hash_value_t hash_value = DJB2_OFFSET;

    while (*used_string)
        hash_value = ((hash_value << 5) + hash_value) + (unsigned char)*used_string++;

    return hash_value;
}

__attribute__((unused)) hash_value_t hash_fnv_generic(const void *data, size_t size_data) {
    const unsigned char* data_single_byte = data;
    hash_value_t hash_value = FNV_OFFSET_BASIS;

    while (size_data--) {
        hash_value = hash_value ^ *data_single_byte++;
        hash_value *= FNV_PRIME;
    }

    return hash_value;
}

__attribute__((unused)) hash_value_t hash_fnv_string(const char used_string[static 1]) {
    hash_value_t hash_value = FNV_OFFSET_BASIS;

    while (*used_string) {
        hash_value = hash_value ^ (unsigned char)*used_string++;
        hash_value *= FNV_PRIME;
    }

    return hash_value;
}

__attribute__((unused)) size_t hash_index_generic(const void *data, size_t size_data, size_t modulo_division) {
    return hash_fnv_generic(data, size_data) % modulo_division;
}

__attribute__((unused)) size_t hash_index_string(const char *used_string, size_t modulo_division) {
    return hash_fnv_string(used_string) % modulo_division;
}
