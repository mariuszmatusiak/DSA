cmake_minimum_required(VERSION 3.29)

set(TARGET_NAME ${LEETCODE_LIB})

add_library(${TARGET_NAME}
    dsa_leetcode.cc
)

target_include_directories(${TARGET_NAME} PUBLIC
    "${PROJECT_SRC_DIR}/utils"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(${TARGET_NAME}
    ${UTILS_LIB}
)

# Enable tests building

# Adding GoogleTest dependency
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # For Windows
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${TARGET_NAME}_Tests
    dsa_leetcode.cc
    dsa_leetcode_tests.cc
)

target_link_libraries(${TARGET_NAME}_Tests  # Link GoogleTest
    GTest::gtest_main
    ${UTILS_LIB}
    ${ALGORITHMS_LIB}
)

include(GoogleTest)
gtest_discover_tests(${TARGET_NAME}_Tests)

# CppCheck execution:
# cppcheck --std=c++20 --enable=all --check-level=exhaustive --language=c++ --cppcheck-build-dir=sca --addon=misra --file-list=cppcheck.cfg
