# Variables set
set(executable_name bf_compiler)

set(bf_compiler_SRC_DIR
    .
)
set(bf_compiler_INCLUDE_DIRS
    .
)
set(bf_compiler_SRC_FILES
    ${bf_compiler_SRC_DIR}/main.cpp
    ${bf_compiler_SRC_DIR}/token.cpp
    ${bf_compiler_SRC_DIR}/tokenize.cpp
)

set(bf_compiler_HEADER_FILES
    ${bf_compiler_INCLUDE_DIRS}/token.hpp
    ${bf_compiler_INCLUDE_DIRS}/tokenize.hpp
)

include_directories(
    ${bf_compiler_INCLUDE_DIRS}
    ${bf_compiler_GENERATED_FILES_DIR}
)

# exe creation
add_executable(${executable_name}
    ${bf_compiler_SRC_FILES}
    ${bf_compiler_HEADER_FILES}
    ${ASM_SOURCE_FILES}
    ${ASM_HEADER_FILES_MACROS}
)

# add depencies
add_dependencies(${executable_name} 
    asm_headers
)

# specify the output directory for the executable
set_target_properties(${executable_name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/
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
