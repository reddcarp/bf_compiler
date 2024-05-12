#include <fstream>
#include <iostream>
#include <string>
#include <set>

#include "tokenize.hpp"
#include "filegen.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./bf_compiler <bf_filepath>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream fs(filename);
    if (!fs.is_open()) {
        std::cerr << "Error: failed to open '" << filename << "'" << std::endl;
        return 1;
    }

    int return_code = 0;
    try {
        std::set<std::string> externs;
        externs.emplace("readData");
        externs.emplace("printData");
        std::unique_ptr<bf_compiler::Token> head = bf_compiler::tokenizeStream(fs, externs);

        bf_compiler::Token* token = head->next_token.get();
        std::ofstream output = bf_compiler::createOutputFile("output.asm", externs);
        while (token != nullptr) {
            token = token->addSegment(output);
        }
        output << "exit EXIT_SUCCESS";
        output.close();

        bf_compiler::createExecutable("output");
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return_code = 1;
    }

    // use -s for link to omit all symbols (makes the binary smaller)

    fs.close();
    return return_code;
}
