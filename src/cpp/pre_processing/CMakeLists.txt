# Variables set
set(executable_name bf_pre_processing)

set(bf_pre_processing_SRC_DIR
    .
)
set(bf_pre_processing_INCLUDE_DIRS
    .
)
set(bf_pre_processing_SRC_FILES
    ${bf_pre_processing_SRC_DIR}/main.cpp
)

file(GLOB_RECURSE bf_pre_processing_HEADER_FILES
)

include_directories(${bf_pre_processing_INCLUDE_DIRS})

# exe creation
add_executable(${executable_name}
    ${bf_pre_processing_SRC_FILES}
    ${bf_pre_processing_HEADER_FILES}
)


set(ASM_HEADER_FILES_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/../bf_compiler/asm_headers
)

set(ASM_HEADER_FILES
    ${ASM_HEADER_FILES_PATH}/asm.hpp
    ${ASM_HEADER_FILES_PATH}/asm_constants.hpp
)

add_custom_command(
    OUTPUT  ${ASM_HEADER_FILES}
    COMMAND ${executable_name} ${ASM_HEADER_FILES_PATH}
    DEPENDS asm_objs ${executable_name}
    COMMENT "Generating asm headers"
)

add_custom_target(asm_headers ALL
    DEPENDS ${ASM_HEADER_FILES}
)