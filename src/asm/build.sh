#!/bin/bash

# directory to store compiled files
mkdir -p ../../build/asm

filesToCompile=('constants' 'printData' 'readData' 'decreaseIndex' 'increaseIndex' 'print' 'start')
# compile all files
for file in "${filesToCompile[@]}"
do
    nasm -f elf64 -o ../../build/asm/$file.o $file.asm
    if [ $? -ne 0 ]; then
        echo "Error compiling $file"
        exit 1
    fi
done

# link all files
# TODO: get the output name from the cpp code
# TODO: only link the needed files
ld -o bf ../../build/asm/*.o
