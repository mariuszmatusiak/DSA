cmake_minimum_required(VERSION 3.29)

set(TARGET_NAME ${UTILS_LIB})

add_library(${TARGET_NAME}
    dsa_utils.cc
)

target_include_directories(${TARGET_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

# target_compile_options(${TARGET_NAME} PUBLIC
#     -Wall -pedantic -O0 --verbose
# )

# target_link_options(${TARGET_NAME} PUBLIC
#     -Wall -O0 -g -pedantic --verbose
# )

# target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)

# Enable tests building

## Adding GoogleTest dependency
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${TARGET_NAME}_Tests
    dsa_utils.cc
    dsa_utils_test.cc
)

target_include_directories(${TARGET_NAME}_Tests PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(${TARGET_NAME}_Tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TARGET_NAME}_Tests)
