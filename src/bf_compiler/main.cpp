#include <fstream>
#include <iostream>
#include <string>
#include <bitset>
#include <stack>
#include <cstdint>

#include "filegen.hpp"

static void handleJumpEnd(std::stack<std::pair<size_t, long>> &jpm_start_stack, std::ofstream &start_asm, uint16_t jpm_index) {
    auto [label_i, start_p ] = jpm_start_stack.top();
    jpm_start_stack.pop();

    start_asm   << "jmpIfDataNotZero .j0b" << std::bitset<16>(label_i) << "\n"
                << ".j0b" << std::bitset<16>(jpm_index) << ":\n";

    // moving stream position to the placeholder of the start jump
    start_asm.seekp(start_p - 17); // 17 because we take the \n into account to not override it
    // replacing the placeholder for the start jump
    start_asm << std::bitset<16>(jpm_index).to_string();
    // reset the stream position to the end of the file
    start_asm.seekp(0, std::ios::end);
}

int main(int argc, char* argv[]) {
     if (argc < 3) {
        std::cout << "Usage: ./bf_compiler <bf_filepath> <output_filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream fs(filename);
    if (!fs.is_open()) {
        std::cerr << "Error: failed to open '" << filename << "'" << std::endl;
        return 1;
    }

    std::ofstream start_asm = bf_compiler::createStartAsm();
    if (!start_asm.is_open()) {
        std::cerr << "Error: failed to create 'start.asm' necessary to produce binary ouput '" << std::endl;
        return 1;
    }

    std::stack<std::pair<size_t, long>> jpm_start_stack;
    uint16_t jpm_index = 0;

    for (char c; fs.get(c);) {
        switch (c) {
            case '>':
                start_asm   << "mov rdi, 1\n"
                            << "call increaseIndex\n";
                break;
            case '<':
                start_asm   << "mov rdi, 1\n"
                            << "call decreaseIndex\n";
                break;
            case '+':
                start_asm << "addToData 1\n";
                break;
            case '-':
                start_asm << "subFromData 1\n";
                break;
            case '.':
                start_asm << "call printData\n";
                break;
            case ',':
                start_asm << "call readData\n";
                break;
            case '[':
                // the length of the placeholder is 16 corresponding to the length of the jump_index
                start_asm  << "jmpIfDataZero .j0bxxxxxxxxxxxxxxxx\n";
                // we store the current index (for the jump end) and the position in the stream (to replace the placeholder later)
                jpm_start_stack.push({jpm_index, start_asm.tellp()});
                start_asm  << ".j0b" << std::bitset<16>(jpm_index) << ":\n";

                jpm_index++;
                break;
            case ']':
                if (jpm_start_stack.empty()) {
                    std::cerr << "Error: missing corresponding `[`" << std::endl;
                    start_asm.close();
                    std::remove("start.asm");
                    return 1;
                }

                handleJumpEnd(jpm_start_stack, start_asm, jpm_index);
                jpm_index++;
                break;
            default:
                break;
        }
    }
    start_asm << "exit EXIT_SUCCESS\n";
    start_asm.close();

    if (!jpm_start_stack.empty()) {
        std::cerr << "Error: missing corresponding `]`" << std::endl;
        std::remove("start.asm");
        return 1;
    }

    return bf_compiler::createExecutable(argv[2]);
}

