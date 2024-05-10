cmake_minimum_required(VERSION 3.5)

PROJECT(bf_compiler
    VERSION 1.0.0
    LANGUAGES CXX
)

# Global CMake variables
set(CMAKE_CXX_STANDARD 20)

# Variables set
set(executable_name bf_compiler)

set(bf_compiler_SRC_DIR
    src/cpp
)
set(bf_compiler_INCLUDE_DIRS
    src/cpp
)
set(bf_compiler_SRC_FILES
    ${bf_compiler_SRC_DIR}/main.cpp
    ${bf_compiler_SRC_DIR}/token.cpp
    ${bf_compiler_SRC_DIR}/tokenize.cpp
)

file(GLOB_RECURSE bf_compiler_HEADER_FILES
    ${bf_compiler_INCLUDE_DIRS}/*.hpp 
)

include_directories(${bf_compiler_INCLUDE_DIRS})

# exe creation
add_executable(${executable_name}
    ${bf_compiler_SRC_FILES}
    ${bf_compiler_HEADER_FILES}
)

# Custom target for tests
# add_custom_target(run_tests COMMAND ctest --output-on-failure)
# add_dependencies(run_tests ${executable_name})

# # Tests
# enable_testing()

# add_test(NAME helloWorldTest
#     COMMAND ${CMAKE_SOURCE_DIR}/test/helloWorldTest.sh
# )

# add_test(NAME memoryLeakTest
#     COMMAND ${CMAKE_SOURCE_DIR}/test/memoryLeakTest.sh
# )

# add_test(NAME userInputTest
#     COMMAND ${CMAKE_SOURCE_DIR}/test/userInputTest.sh
# )

# add_test(NAME errorNoMatchingEndBracket
#     COMMAND ${CMAKE_SOURCE_DIR}/test/errorNoMatchingEndBracket.sh
# )

# add_test(NAME errorNoMatchingStartBracket
#     COMMAND ${CMAKE_SOURCE_DIR}/test/errorNoMatchingStartBracket.sh
# )

# add_test(NAME errorDataPointerOutOfBound
#     COMMAND ${CMAKE_SOURCE_DIR}/test/errorDataPointerOutOfBound.sh
# )
