cmake_minimum_required(VERSION 3.22) # The minimum CMake version used.
project(HASH) # Name of the current project.

add_executable(HASH) # Define a name for your executable.

set(target HASH) # Create a name for your target.

# Here, you can add the files you want to add to your executable.
target_sources(${target}
        PRIVATE
        main.c # The main file of the project.

        ./src/hash.c
        ./src/test.c
        )

include_directories(./inc) # Instruct the compiler where to look for the given header files within this project.

target_compile_features(${target} PRIVATE c_std_23) # We are using the newest language standards, so C23.
set_target_properties(${target} PROPERTIES C_EXTENSIONS OFF) # Turn of compiler specific language extensions.

# Set the options for GNU-linke compilers:
target_compile_options(${target} PRIVATE
        # Set all warnings for all the build types.
        $<$<C_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic -Werror -fno-omit-frame-pointer>
        # Optimisation for 'Release' mode.
        $<$<AND:$<C_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Release>>:-O3>
        # Optimisation in 'Debug'.
        $<$<AND:$<C_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Debug>>:-Og -g>
        )

# Set options for MSVC
target_compile_options(${target} PRIVATE
        # set warnings for all build types
        $<$<C_COMPILER_ID:MSVC>:/Wall>
        # Optimisation for 'Release' mode.
        $<$<AND:$<C_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/O2>
        # Optimisation in 'Debug'.
        $<$<AND:$<C_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/RTC1 /Od /Zi>
        )

# Enable the 'Address Sanitizer'.
option(USE_ASAN "Use address sanitizer if available" OFF) # Fancy message. It shows how to turn of the 'Address Sanitizer'.

# Try to find the path of your 'Address Sanitizer'.
execute_process(COMMAND "${CMAKE_C_COMPILER}" -print-file-name=libasan.so
        OUTPUT_VARIABLE LIBASAN_PATH
        RESULT_VARIABLE ASAN_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE)

set(HAS_ASAN FALSE)

# Check if the path of the 'Address Sanitizer' is found.
if (USE_ASAN AND (${ASAN_RESULT} EQUAL 0) AND (NOT ${LIBASAN_PATH} STREQUAL ""))
    message("libasan found @${LIBASAN_PATH}") # Show the path of the sanitizer.
    message("To disable the address sanitizer set USE_ASAN to OFF.\n") # Show how to turn off the address sanitizer.
    set(HAS_ASAN TRUE) # Now, your sanitizer is enabled.
endif ()

if (HAS_ASAN AND USE_ASAN)
    target_compile_options(${target} PRIVATE -fsanitize=address) # Set the target compile options for the sanitizer.
    target_link_options(${target} PRIVATE -fsanitize=address) # The link options for the sanitizer.
endif ()


# The available hash sizes are in the case 32 bits or 64 bits.
# Within this project are 32-bits hash sizes used!
set(HASH_SIZE_SUPPORT 32)

target_compile_definitions(HASH PRIVATE HASH_BITS=${HASH_SIZE_SUPPORT})