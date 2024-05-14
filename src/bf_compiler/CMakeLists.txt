set(executable_name bf_compiler)

set(bf_compiler_SRC_DIR
    .
)
set(bf_compiler_INCLUDE_DIRS
    .
)
set(bf_compiler_SRC_FILES
    ${bf_compiler_SRC_DIR}/main.cpp
    ${bf_compiler_SRC_DIR}/filegen.cpp
)

set(bf_compiler_HEADER_FILES
    ${bf_compiler_INCLUDE_DIRS}/filegen.hpp
)

include_directories(
    ${bf_compiler_INCLUDE_DIRS}
    ${asm_cpp_embedder_GENERATED_FILES_DIR}
)

# exe creation
add_executable(${executable_name}
    ${bf_compiler_SRC_FILES}
    ${bf_compiler_HEADER_FILES}
    ${ASM_CPP_FILES}
    ${ASM_MACROS_CPP_FILES}
)

# add depencies
add_dependencies(${executable_name} 
    asm_cpp_files
)

# specify the output directory for the executable
set_target_properties(${executable_name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/
)
