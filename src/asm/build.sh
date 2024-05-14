#!/bin/bash

# directory to store compiled files
mkdir -p build

filesToCompile=('constants' 'printData' 'data' 'readData' 'decreaseIndex' 'increaseIndex' 'print' 'start')
# compile all files
for file in "${filesToCompile[@]}"
do
    nasm -f elf64 -o build/$file.o $file.asm
    if [ $? -ne 0 ]; then
        echo "Error compiling $file"
        exit 1
    fi
done

# link all files
ld -o bf build/*.o
