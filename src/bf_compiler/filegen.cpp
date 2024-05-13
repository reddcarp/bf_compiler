#include<map>
#include <vector>

#include "filegen.hpp"
#include "macros.hpp"
#include "decreaseIndex.hpp"
#include "increaseIndex.hpp"
#include "constants.hpp"
#include "data.hpp"
#include "print.hpp"
#include "printData.hpp"
#include "readData.hpp"

namespace bf_compiler {

std::vector<std::string> asmObjects;

void deleteFiles(const std::string &filename) {
    std::string command = "rm -f " + filename + ".o "  + filename + ".asm ";
    for (const std::string &asmObject : asmObjects) {
        command +=  asmObject + ".o ";
    }
    if (std::system(command.c_str()) != 0) {
        throw std::runtime_error("Error: failed to delete files");
    }
}

void recreateAsmObjectFiles() {
    std::ofstream decreaseIndex("decreaseIndex.o", std::ios::binary);
    decreaseIndex.write(reinterpret_cast<char*>(___asm_decreaseIndex_o), ___asm_decreaseIndex_o_len);

    std::ofstream increaseIndex("increaseIndex.o", std::ios::binary);
    increaseIndex.write(reinterpret_cast<char*>(___asm_increaseIndex_o), ___asm_increaseIndex_o_len);

    std::ofstream constants("constants.o", std::ios::binary);
    constants.write(reinterpret_cast<char*>(___asm_constants_o), ___asm_constants_o_len);

    std::ofstream data("data.o", std::ios::binary);
    data.write(reinterpret_cast<char*>(___asm_data_o), ___asm_data_o_len);

    std::ofstream print("print.o", std::ios::binary);
    print.write(reinterpret_cast<char*>(___asm_print_o), ___asm_print_o_len);

    std::ofstream printData("printData.o", std::ios::binary);
    printData.write(reinterpret_cast<char*>(___asm_printData_o), ___asm_printData_o_len);

    std::ofstream readData("readData.o", std::ios::binary);
    readData.write(reinterpret_cast<char*>(___asm_readData_o), ___asm_readData_o_len);

    asmObjects = {"decreaseIndex", "increaseIndex", "constants", "data", "print", "printData", "readData"};
}

void createMacroFile() {
    std::ofstream output("macros.asm");
    if (!output.is_open()) {
        throw std::runtime_error("Error: failed to open 'macros.asm'");
    }

    output  << macros_asm;
}

void deleteMacroFile() {
    std::string command = "rm -f macros.asm";
    if (std::system(command.c_str()) != 0) {
        throw std::runtime_error("Error: failed to delete 'macros.asm'");
    }
}

std::ofstream createOutputFile(const std::string &filename, const std::set<std::string> &externs) {
    std::ofstream output(filename + ".asm");
    if (!output.is_open()) {
        throw std::runtime_error("Error: failed to open '" + filename + ".asm'");
    }

    // Template for the start of the assembly file
    output  << "%include \"macros.asm\"\n";
    for (const std::string &extern_name : externs) {
        output << "extern " << extern_name << "\n";
    }
    output  << "extern EXIT_SUCCESS\n"
            << "section .text\n"
            << "global _start\n"
            << "_start:\n";

    return output;
}

void createExecutable(const std::string &filename) {
    createMacroFile();
    std::string command = "nasm -f elf64 " + filename + ".asm -o " + filename + ".o";
    if (std::system(command.c_str()) != 0) {
        throw std::runtime_error("Error: failed to assemble '" + filename + ".asm'");
    }
    deleteMacroFile();

    recreateAsmObjectFiles();

    command = "ld -s -o " + filename + " " + filename + ".o";

    for (const std::string &asmObject : asmObjects) {
        command += " " + asmObject + ".o";
    }

    if (std::system(command.c_str()) != 0) {
        throw std::runtime_error("Error: failed to link '" + filename + "'");
    }

    deleteFiles(filename);
}

} // bf_compiler