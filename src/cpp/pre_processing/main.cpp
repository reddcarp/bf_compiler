#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    // TODO: create .hpp files from object files and macros.asm files

    if (std::ofstream file(argv[2]); file.is_open()) {
        file << "Hello, World!" << std::endl;
        return 0;
    }

    return 1;
}