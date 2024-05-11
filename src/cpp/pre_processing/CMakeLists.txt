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

foreach(asm_source ${ASM_SOURCE_FILES})
    get_filename_component(asm_source_filename ${asm_source} NAME_WE)
    add_custom_command(
        OUTPUT ${asm_source}
        COMMAND xxd -i ../../asm/${asm_source_filename}.o > ${asm_source}
        DEPENDS ../../asm/${asm_source_filename}.o
        COMMENT "Generating .cpp for ${asm_source_filename}.o"
    )

    set(asm_header "${bf_compiler_GENERATED_FILES_DIR}/${asm_source_filename}.hpp")
    add_custom_command(
        OUTPUT ${asm_header}
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/generate_hpp.sh ${asm_header} ${asm_source_filename}
        DEPENDS ${asm_source}
        COMMENT "Generating .hpp for ${asm_source_filename}.cpp"
    )
    list(APPEND ASM_SOURCE_HEADER_FILES ${asm_header})
endforeach()

# Different treatment for macros files
foreach(asm_macro_header ${ASM_HEADER_FILES_MACROS})
    get_filename_component(asm_macro_filename ${asm_macro_header} NAME_WE)
    add_custom_command(
        OUTPUT ${asm_macro_header}
        COMMAND ${executable_name} ${ASM_FILEPATH}/${asm_macro_filename}.asm ${asm_macro_header} 1
        DEPENDS ${ASM_FILEPATH}/${asm_macro_filename}.asm
        COMMENT "Generating header for ${asm_macro_filename}.asm"
    )
endforeach()


add_custom_target(asm_sources ALL
DEPENDS asm_objs ${ASM_SOURCE_FILES}
)

add_custom_target(asm_headers ALL
    DEPENDS asm_sources ${ASM_SOURCE_HEADER_FILES} ${ASM_HEADER_FILES_MACROS}
)