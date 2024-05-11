# bf_compiler

A brainfck language compiler for linux x86_64 intel architecture, written in C++

## requirements

- xxd
- nasm

## TODO: Structure of the compilation

bash -> creates .o asm files
bf_pre_processing -> creates .cpp asm files from .o (will be baked in the bf_compiler exe)
bf_pre_processing -> creates .hpp asm files from .cpp (will be baked in the bf_compiler exe)
bf_pre_processing -> creates .cpp asm files from macros.asm specific treatment to separate the macros)
bf_pre_processing -> creates .hpp asm files from macros.cpp specific treatment to separate the macros)
bf_compiler gets built

ONLY the files that changed get recreated
exemple:
    data.asm change
        bash -> create data.o
        bd_pre_processing -> creates data.cpp
        bd_pre_processing -> creates data.hpp
        bf_compiler gets re-built

    macros.asm change
        pre_processing -> creates macros.cpp
        pre_processing -> creates macros.hpp
        bf_compiler gets re-built

## Commands

```bash
make -p build/
cd build/
cmake ../
make
```

## TEsts

manual -> able to use build.sh to create a custom start and test out the .asm files on their own

## Resources

- <http://www.egr.unlv.edu/~ed/assembly64.pdf> ❤️
- <https://www.nasm.us/doc/nasmdoc0.html?ref=conradk.com>
- <https://p403n1x87.github.io/getting-started-with-x86-64-assembly-on-linux.html>
- <https://markfloryan.github.io/pdr/slides/reiss/asm.pdf>
- <https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf>
- <https://web.stanford.edu/class/archive/cs/cs107/cs107.1196/resources/onepage_x86-64.pdf>
