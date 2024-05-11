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

set(ASM_FILEPATH
    ${CMAKE_CURRENT_SOURCE_DIR}/../../asm
)

set(ASM_HEADER_FILES
    ${bf_compiler_GENERATED_FILES_DIR}/constants.hpp
    ${bf_compiler_GENERATED_FILES_DIR}/data.hpp
    ${bf_compiler_GENERATED_FILES_DIR}/decreaseIndex.hpp
    ${bf_compiler_GENERATED_FILES_DIR}/increaseIndex.hpp
    ${bf_compiler_GENERATED_FILES_DIR}/print.hpp
    ${bf_compiler_GENERATED_FILES_DIR}/printData.hpp
    ${bf_compiler_GENERATED_FILES_DIR}/readData.hpp
)
foreach(asm_header ${ASM_HEADER_FILES})
    get_filename_component(asm_header_filename ${asm_header} NAME_WE)
    add_custom_command(
        OUTPUT ${asm_header}
        COMMAND ${executable_name} ../../asm/${asm_header_filename}.o ${asm_header} 0
        DEPENDS ../../asm/${asm_header_filename}.o
        COMMENT "Generating header for ${asm_header_filename}.o"
    )
endforeach()

# Different treatment for macros files
set(ASM_HEADER_FILES_MACROS
    ${bf_compiler_GENERATED_FILES_DIR}/macros.hpp
)
foreach(asm_macro_header ${ASM_HEADER_FILES_MACROS})
    get_filename_component(asm_macro_filename ${asm_macro_header} NAME_WE)
    add_custom_command(
        OUTPUT ${asm_macro_header}
        COMMAND ${executable_name} ${ASM_FILEPATH}/${asm_macro_filename}.asm ${asm_macro_header} 1
        DEPENDS ${ASM_FILEPATH}/${asm_macro_filename}.asm
        COMMENT "Generating header for ${asm_macro_filename}.asm"
    )
endforeach()

add_custom_target(asm_headers ALL
    DEPENDS asm_objs ${ASM_HEADER_FILES} ${ASM_HEADER_FILES_MACROS}
)