cmake_minimum_required(VERSION 3.29)

# This creates DSA_VERSION_MAJOR and DSA_VERSION_MINOR
project(DSA VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20) # Sets standard to std=c++20
set(CMAKE_CXX_STANDARD_REQUIRED True) # Sets standard as required
# Override CMAKE_BUILD_TYPE passed by cmd line
# set(CMAKE_BUILD_TYPE Debug)

# Globally overriden CMAKE_CXX_FLAGS, further updated also by the add_compile_options
# set(CMAKE_C_FLAGS ...)   # Initialized by the CFLAGS environment variable, unused
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++20")  # Initialized by the CXXFLAGS environment variable.

# Additional common compiler options for current and subsequent directories options (global here)
add_compile_options(-pedantic --verbose)

# Doesn't provide binaries (linker error)
# add_compile_options(--analyzer-output html --analyze)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-O0 -g -DDEBUG)
else()
    add_compile_options(-O2)
endif()

# Common preprocessor definitions
# add_compile_definitions()

# Common include directories
# include_directories()

# Target-specific compile options
# target_compile_options()

set(UTILS_LIB       "DSA_Utils_Lib")
set(STRUCTURES_LIB  "DSA_Structures_Lib")
set(ALGORITHMS_LIB  "DSA_Algorithms_Lib")
set(LEETCODE_LIB    "DSA_LeetCode_Lib")
set(MODERN_CPP_BIN  "DSA_Modern_cpp")

add_subdirectory(utils)
add_subdirectory(structures)
add_subdirectory(algorithms)
add_subdirectory(leetcode_solutions)
add_subdirectory(modern_cpp)
