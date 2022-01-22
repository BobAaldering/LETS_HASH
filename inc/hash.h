#ifndef HASH_HASH_H
#define HASH_HASH_H

#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>

#if !defined(HASH_BITS)
    // Change this values to either 32-bits or 64-bits.
    #define HASH_BITS_USAGE (32)
#endif

#if defined(HASH_BITS)
    #if (HASH_BITS == 32)
        typedef uint32_t hash_value_t;
        #define HASH_FORMAT PRIu32
    #elif (HASH_BITS == 64)
        typedef uint64_t hash_t;
        #define HASH_FORMAT PRIu64
    #else
        #error "Only hash sizes of 32 and 64 bits are supported."
    #endif
#endif

extern int get_hash_bits();

extern hash_value_t hash_djb2_generic(const void* data, size_t size_data);
extern hash_value_t hash_djb2_string(const char used_string[static 1]);

extern hash_value_t hash_fnv_generic(const void* data, size_t size_data);
extern hash_value_t hash_fnv_string(const char used_string[static 1]);

extern size_t hash_index_generic(const void* data, size_t size_data, size_t modulo_division);
extern size_t hash_index_string(const char* used_string, size_t modulo_division);

#endif
