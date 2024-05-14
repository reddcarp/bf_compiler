#include <iostream>
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

static const std::vector<std::string> asmObjects = {"decreaseIndex", "increaseIndex", "constants", "data", "print", "printData", "readData"};

int deleteFiles() {
    std::string command = "rm -f start.o start.asm ";
    for (const std::string &asmObject : asmObjects) {
        command +=  asmObject + ".o ";
    }
    if (std::system(command.c_str()) != 0) {
        std::cerr << "Warning: failed to delete object files" << std::endl;
        return 1;
    }

    return 0;
}

void recreateAsmObjFile(const std::string &filename, const char *data, unsigned int len) {
    std::ofstream output(filename, std::ios::binary);
    if (!output.is_open()) {
        throw std::ios_base::failure("Error: failed to create '" + filename + "'");
    }
    output.write(data, len);
}

void recreateAsmObjectFiles() {
    recreateAsmObjFile("decreaseIndex.o", reinterpret_cast<char*>(___asm_decreaseIndex_o), ___asm_decreaseIndex_o_len);
    recreateAsmObjFile("increaseIndex.o", reinterpret_cast<char*>(___asm_increaseIndex_o), ___asm_increaseIndex_o_len);
    recreateAsmObjFile("constants.o", reinterpret_cast<char*>(___asm_constants_o), ___asm_constants_o_len);
    recreateAsmObjFile("data.o", reinterpret_cast<char*>(___asm_data_o), ___asm_data_o_len);
    recreateAsmObjFile("print.o", reinterpret_cast<char*>(___asm_print_o), ___asm_print_o_len);
    recreateAsmObjFile("printData.o", reinterpret_cast<char*>(___asm_printData_o), ___asm_printData_o_len);
    recreateAsmObjFile("readData.o", reinterpret_cast<char*>(___asm_readData_o), ___asm_readData_o_len);
}

void createMacroFile() {
    std::ofstream output("macros.asm");
    if (!output.is_open()) {
        throw std::ios_base::failure("Error: failed to open 'macros.asm'");
    }

    output << macros_asm;
}

int deleteMacroFile() {
    if (std::string command = "rm -f macros.asm"; std::system(command.c_str()) != 0) {
        std::cerr << "Warning: failed to delete 'macros.asm'" << std::endl;
        return 1;
    }

    return 0;
}

std::ofstream createStartAsm() {
    std::ofstream start_asm("start.asm");
    if (!start_asm.is_open()) {
        throw std::ios_base::failure("Error: failed to open 'start.asm'");
    }

    // Template for the start of the assembly file
    start_asm  << "%include \"macros.asm\"\n";
    start_asm << R"(
extern decreaseIndex
extern increaseIndex
extern printData
extern readData
extern EXIT_SUCCESS
extern dataArr, dataIndex
)";
    start_asm  << "section .text\n"
            << "global _start\n"
            << "_start:\n";

    return start_asm;
}

int createExecutable(const std::string &filename) {
    createMacroFile();
    std::string command = "nasm -f elf64 -o start.o start.asm ";
    if (std::system(command.c_str()) != 0) {
        std::cerr << "Error: failed produce 'start.o'" << std::endl;
        return 1;
    }
    int ret = deleteMacroFile();

    recreateAsmObjectFiles();

    command = "ld -s -o " + filename + " start.o";
    for (const std::string &asmObject : asmObjects) {
        command += " " + asmObject + ".o";
    }
    if (std::system(command.c_str()) != 0) {
        deleteFiles();
        std::cerr << "Error: failed to link '" + filename + "'" << std::endl;
        return 1;
    }

    ret = deleteFiles() != 0 ? 1 : ret;
    return ret;
}

} // bf_compiler