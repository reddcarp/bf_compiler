<p align="center">
  <img src="screenshots/Icon.png" width="200">
</p>

<h1 align="center">BF compiler</h1>

<p align="center">
  <strong>A <a href="https://en.wikipedia.org/wiki/Brainfuck">brainfck</a> language compiler for linux x86_64 intel architecture, written in C++.</strong>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/language-cpp-orange.svg" alt="Language">
  <img src="https://img.shields.io/badge/platform-BF-blue.svg" alt="Platform">
  <img src="https://img.shields.io/badge/license-MIT-green.svg" alt="License">
</p>

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

> Note: all the lines of asm code are commented to explain their purpose.

## Resources

- <http://www.egr.unlv.edu/~ed/assembly64.pdf> ❤️
- <https://www.nasm.us/doc/nasmdoc0.html?ref=conradk.com>
- <https://p403n1x87.github.io/getting-started-with-x86-64-assembly-on-linux.html>
- <https://markfloryan.github.io/pdr/slides/reiss/asm.pdf>
- <https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf>
- <https://web.stanford.edu/class/archive/cs/cs107/cs107.1196/resources/onepage_x86-64.pdf>