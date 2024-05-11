# bf_compiler

A brainfck language compiler for linux x86_64 intel architecture, written in C++

## TODO: Structure of the compilation

bash -> creates .o asm files
bf_pre_processing -> creates .hpp asm files from .o and macros.asm (will be baked in the bf_compiler exe)
bf_compiler gets built

ONLY the files that changed get recreated
exemple:
    data.asm change
        bash -> create data.o
        bd_pre_processing -> creates data.hpp
        bf_compiler gets re-built

## Commands

```bash
make -p build/cpp
cd build/cpp
cmake ../..
make
```

## Resources

- <http://www.egr.unlv.edu/~ed/assembly64.pdf> ❤️
- <https://www.nasm.us/doc/nasmdoc0.html?ref=conradk.com>
- <https://p403n1x87.github.io/getting-started-with-x86-64-assembly-on-linux.html>
- <https://markfloryan.github.io/pdr/slides/reiss/asm.pdf>
- <https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf>
- <https://web.stanford.edu/class/archive/cs/cs107/cs107.1196/resources/onepage_x86-64.pdf>
