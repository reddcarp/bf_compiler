# bf_compiler

A [brainfck](https://en.wikipedia.org/wiki/Brainfuck) language compiler for linux x86_64 intel architecture, written in C++.

## Compilation

requirements:

- xxd package
- nasm package

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

```bash
./bf_compiler <bf_filepath> <output_filename>
```

## Example

```bash
./bf_compiler ../bf_scripts/hello_world.bf out
./out
```

## Tests

### Automatic validation tests

Requirements:

- shunit2 package
- valgrind package

Run all tests:

```bash
make run_tests
```

### Manual asm test

In src/asm, change the content of the start.asm file and run ./build.sh.
It will create the executable without symbol stripping. Perfect to try the behavior of the base asm code and understand it more.

ps: all the lines of asm code are commented and explaining their purpose.

## Resources

- <http://www.egr.unlv.edu/~ed/assembly64.pdf> ❤️
- <https://www.nasm.us/doc/nasmdoc0.html?ref=conradk.com>
- <https://p403n1x87.github.io/getting-started-with-x86-64-assembly-on-linux.html>
- <https://markfloryan.github.io/pdr/slides/reiss/asm.pdf>
- <https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf>
- <https://web.stanford.edu/class/archive/cs/cs107/cs107.1196/resources/onepage_x86-64.pdf>