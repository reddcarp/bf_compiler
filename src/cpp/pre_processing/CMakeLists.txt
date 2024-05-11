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
        DEPENDS ${ASM_FILEPATH}/${asm_source_filename}.asm
        COMMENT "Generating .hpp for ${asm_source_filename}.asm"
    )
    list(APPEND ASM_SOURCE_HEADER_FILES ${asm_header})
endforeach()

# Different treatment for macros files
foreach(asm_macro_source ${ASM_MACROS_SOURCE_FILES})
    get_filename_component(asm_macro_filename ${asm_macro_source} NAME_WE)
    add_custom_command(
        OUTPUT ${asm_macro_source} ${bf_compiler_GENERATED_FILES_DIR}/${asm_macro_filename}.hpp
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/generate_macro_files.sh ${ASM_FILEPATH}/${asm_macro_filename}.asm ${asm_macro_source} ${bf_compiler_GENERATED_FILES_DIR}/${asm_macro_filename}.hpp ${asm_macro_filename}
        DEPENDS ${ASM_FILEPATH}/${asm_macro_filename}.asm
        COMMENT "Generating .hpp and .cpp for ${asm_macro_filename}.asm"
    )
endforeach()

add_custom_target(asm_macros ALL
    DEPENDS ${ASM_MACROS_SOURCE_FILES}
)

add_custom_target(asm_headers ALL
    DEPENDS ${ASM_SOURCE_HEADER_FILES}
)

add_custom_target(asm_sources ALL
    DEPENDS asm_objs asm_macros asm_headers ${ASM_SOURCE_FILES}
)
