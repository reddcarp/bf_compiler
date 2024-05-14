#ifndef BF_COMPILER_FILEGEN_HPP
#define BF_COMPILER_FILEGEN_HPP

#include <string>
#include <fstream>

namespace bf_compiler {

std::ofstream createStartAsm();
int createExecutable(const std::string &filename);

} // bf_compiler

#endif // BF_COMPILER_FILEGEN_HPP