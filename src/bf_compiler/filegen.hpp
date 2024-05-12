#ifndef BF_COMPILER_FILEGEN_HPP
#define BF_COMPILER_FILEGEN_HPP

#include <set>
#include <string>
#include <fstream>

namespace bf_compiler {

std::ofstream createOutputFile(const std::string &filename, const std::set<std::string> &externs);
void createExecutable(const std::string &filename);

} // bf_compiler

#endif // BF_COMPILER_FILEGEN_HPP