set(ASM_FILEPATH
    ${CMAKE_CURRENT_SOURCE_DIR}/../asm
)

foreach(asm_cpp_file ${ASM_CPP_FILES})
    get_filename_component(asm_source_filename ${asm_cpp_file} NAME_WE)
    add_custom_command(
        OUTPUT ${asm_cpp_file}
        COMMAND xxd -i ../asm/${asm_source_filename}.o > ${asm_cpp_file}
        DEPENDS ../asm/${asm_source_filename}.o
        COMMENT "Generating .cpp for ${asm_source_filename}.o"
    )

    set(asm_header "${asm_cpp_embedder_GENERATED_FILES_DIR}/${asm_source_filename}.hpp")
    add_custom_command(
        OUTPUT ${asm_header}
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/generate_hpp.sh ${asm_header} ${asm_source_filename}
        DEPENDS ${ASM_FILEPATH}/${asm_source_filename}.asm
        COMMENT "Generating .hpp for ${asm_source_filename}.asm"
    )
    list(APPEND ASM_HPP_FILES ${asm_header})
endforeach()

# Different treatment for macros files
foreach(asm_macro_source ${ASM_MACROS_CPP_FILES})
    get_filename_component(asm_macro_filename ${asm_macro_source} NAME_WE)
    add_custom_command(
        OUTPUT ${asm_macro_source} ${asm_cpp_embedder_GENERATED_FILES_DIR}/${asm_macro_filename}.hpp
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/generate_macro_files.sh ${ASM_FILEPATH}/${asm_macro_filename}.asm ${asm_macro_source} ${asm_cpp_embedder_GENERATED_FILES_DIR}/${asm_macro_filename}.hpp ${asm_macro_filename}
        DEPENDS ${ASM_FILEPATH}/${asm_macro_filename}.asm
        COMMENT "Generating .hpp and .cpp for ${asm_macro_filename}.asm"
    )
endforeach()

add_custom_target(asm_macros_cpp_hpp_files ALL
    DEPENDS ${ASM_MACROS_CPP_FILES}
)

add_custom_target(asm_hpp_files ALL
    DEPENDS ${ASM_HPP_FILES}
)

add_custom_target(asm_cpp_files ALL
    DEPENDS asm_objs asm_macros_cpp_hpp_files asm_hpp_files ${ASM_CPP_FILES}
)
