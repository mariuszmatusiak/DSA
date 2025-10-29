cmake_minimum_required(VERSION 3.29)

set(TARGET_NAME ${STRUCTURES_LIB})

# Commented out until a source file is available

# add_library(${TARGET_NAME}
#
# )

# target_include_directories(${TARGET_NAME} PUBLIC
#    "${CMAKE_CURRENT_SOURCE_DIR}"
# )

# target_compile_options(${TARGET_NAME} PUBLIC
#     -Wall -pedantic -O0 --verbose
# )

# target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)

# target_link_libraries(${TARGET_NAME}
#    ${UTILS_LIB}
# )

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
    dsa_structures_test.cc
)

target_link_libraries(${TARGET_NAME}_Tests
    ${UTILS_LIB}
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TARGET_NAME}_Tests)

# CppCheck execution:
# cppcheck --std=c++20 --enable=all --check-level=exhaustive --language=c++ --cppcheck-build-dir=sca --addon=misra --file-list=cppcheck.cfg
