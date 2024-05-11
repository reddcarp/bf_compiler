#!/bin/bash

# This script generates the hpp and cpp files for macros.asm
asm_filepath=$1
source_filename=$2
header_filepath=$3
filename=$4

# creating the source file
echo "#include \"${filename}.hpp\"" > "${source_filename}"
echo "" >> "${source_filename}"
echo "std::string ${filename}_asm = R\"(" >> "${source_filename}"
cat "${asm_filepath}" >> "${source_filename}"
echo "" >> "${source_filename}"
echo ")\";" >> "${source_filename}"

# creating the header file
echo "#ifndef ASM_${filename}_HPP" > "${header_filepath}"
echo "#define ASM_${filename}_HPP" >> "${header_filepath}"
echo "" >> "${header_filepath}"
echo "#include <string>" >> "${header_filepath}"
echo "" >> "${header_filepath}"
echo "extern std::string ${filename}_asm;" >> "${header_filepath}"
echo "" >> "${header_filepath}"
echo "#endif" >> "${header_filepath}"
