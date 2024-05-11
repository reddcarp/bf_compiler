# This file will be used to generate the object files from the asm files

# List of source asm files
set(SOURCE_FILES
    constants.asm
    data.asm
    decreaseIndex.asm
    increaseIndex.asm
    macros.asm
    print.asm
    printData.asm
    readData.asm
)

# List of object files to be generated
set(OBJECT_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/constants.o
    ${CMAKE_CURRENT_BINARY_DIR}/data.o
    ${CMAKE_CURRENT_BINARY_DIR}/decreaseIndex.o
    ${CMAKE_CURRENT_BINARY_DIR}/increaseIndex.o
    ${CMAKE_CURRENT_BINARY_DIR}/print.o
    ${CMAKE_CURRENT_BINARY_DIR}/printData.o
    ${CMAKE_CURRENT_BINARY_DIR}/readData.o
)

# Add custom command to generate object files
foreach(asm_file ${SOURCE_FILES})
    get_filename_component(asm_file_name ${asm_file} NAME_WE)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${asm_file_name}.o
        COMMAND nasm -f elf64 -o ${CMAKE_CURRENT_BINARY_DIR}/${asm_file_name}.o ${asm_file}
        DEPENDS ${asm_file}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating object file for ${asm_file}"
    )
endforeach()

# add custom target for pre_processing
add_custom_target(asm_objs
    DEPENDS ${OBJECT_FILES}
)