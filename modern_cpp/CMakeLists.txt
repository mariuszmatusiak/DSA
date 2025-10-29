cmake_minimum_required(VERSION 3.29)

set(TARGET_NAME ${MODERN_CPP_BIN})

configure_file(dsa_config.h.in dsa_config.h) # This populates variables and creates header file

add_executable(${TARGET_NAME}
    dsa_main_cpp.cc
    dsa_classes.cc
)

target_include_directories(${TARGET_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../utils"
    "${CMAKE_CURRENT_SOURCE_DIR}/../structures"
    "${PROJECT_BINARY_DIR}/modern_cpp"  # This tells CMake to add output folder to include dirs
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(${TARGET_NAME}
    ${UTILS_LIB}
    ${ALGORITHMS_LIB}
)

# CppCheck execution:
# cppcheck --std=c++20 --enable=all --check-level=exhaustive --language=c++ --cppcheck-build-dir=sca --addon=misra --file-list=cppcheck.cfg
