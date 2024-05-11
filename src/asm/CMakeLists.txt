foreach(asm_file ${ASM_CPP_FILES})
    get_filename_component(asm_file_name ${asm_file} NAME_WE)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${asm_file_name}.o
        COMMAND nasm -f elf64 -o ${CMAKE_CURRENT_BINARY_DIR}/${asm_file_name}.o ${asm_file_name}.asm
        DEPENDS ${asm_file_name}.asm
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating .o for ${asm_file_name}.asm"
    )
    list(APPEND OBJECT_FILES ${CMAKE_CURRENT_BINARY_DIR}/${asm_file_name}.o)
endforeach()

# cistom target to create object files from assembly files
add_custom_target(asm_objs
    DEPENDS ${OBJECT_FILES}
)