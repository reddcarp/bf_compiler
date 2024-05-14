#!/bin/bash

# This script generates the hpp files for the pre-processing stage
header_filepath=$1
source_filename=$2

echo "#ifndef ASM_${source_filename}_HPP" > "${header_filepath}"
echo "#define ASM_${source_filename}_HPP" >> "${header_filepath}"
echo "" >> "${header_filepath}"
echo "extern unsigned char ___asm_${source_filename}_o[];" >> "${header_filepath}"
echo "extern unsigned int ___asm_${source_filename}_o_len;" >> "${header_filepath}"
echo "" >> "${header_filepath}"
echo "#endif" >> "${header_filepath}"