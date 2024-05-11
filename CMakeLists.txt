cmake_minimum_required(VERSION 3.5)

PROJECT(bf_compiler
    VERSION 1.0.0
    LANGUAGES CXX
)

# Global CMake variables
set(CMAKE_CXX_STANDARD 20)

# TODO: put more config options here

set(bf_compiler_GENERATED_FILES_DIR
    ${CMAKE_BINARY_DIR}/generated
)
file(MAKE_DIRECTORY ${bf_compiler_GENERATED_FILES_DIR})

add_subdirectory(src/asm)
add_subdirectory(src/cpp/pre_processing)
add_subdirectory(src/cpp/bf_compiler)
