# Do you want a hash?

##### Pay attention! This repository is currently under construction! Functions will be added to it.

The mother of all programming languages, that is of course C! Everyone knows, of course, that C itself does not have many data structures, such as a hash map for example. In addition, of course, it also has no hash function. For this reason, this repository provides an implementation of several hash functions, in this case `Fowler-Noll-Vo 1A` (also called `FNV-1A`) and the `dbj2` hash functions.

So: do you want a better insight into various hash functions, with an implementation within the C programming language? Then you've come to the right place! And 👀 no further! 

## Creating a hash

It is very easy to create a hash, just by calling the function `hash_fnv_string`, in this case generating a representative hash of a string. To give an example of a corresponding hash, this can be done as follows:

```c
#include <stdio.h>
#include "hash.h"

int main() {
    const char* str = "Do you want a hash?";
    printf("Hashed value: %u", hash_fnv_string(str)); // This creates the hash, following FNV-1A, 1097005601 (using 32-bits). 

    return 0;
}
```

You can see that the hash `1097005601` has been generated from the relevant string, but note that in this case 32-bits have been used. Of course you can also call other functions, from which just a hash can be generated, since for example `void*` is used to allow various types. If you want to generate a hash of a string, this string must exist, because `const char used_string [static 1]` is used in the implementation.

## Supported hash sizes

In this project you can work with different hash sizes, which are given in bits. Support is provided for both 32-bit and 64-bit. You can change this in the corresponding [CMakeLists.txt](CMakeLists.txt) of this project. Within this is a specific variable, which is applied to the corresponding target. If you specify values other than 32-bit or 64-bit it will roughly not compile. To change the size you need to change the following variable in the CMakeLists.txt:

```cmake
# The available hash sizes are in the case 32 bits or 64 bits.
# Within this project are 32-bits hash sizes used!
set(HASH_SIZE_SUPPORT 32) # Change this value to either 32-bits, or 64 bits!

target_compile_definitions(HASH PRIVATE HASH_BITS=${HASH_SIZE_SUPPORT})
```

You can see that in the above code snippet the variable `set(HASH_SIZE_SUPPORT 32)` needs to be changed. Based on this, the program will compile. 
