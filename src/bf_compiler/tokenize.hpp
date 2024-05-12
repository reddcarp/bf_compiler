#ifndef BF_COMPILER_TOKENIZE_HPP
#define BF_COMPILER_TOKENIZE_HPP

#include <memory>
#include <set>

#include "token.hpp"

namespace bf_compiler {

/**
 * Tokenizes the input stream and returns a unique pointer to a Token object.
 *
 * @param stream The input stream to tokenize.
 * @return A unique pointer to a Token object representing the tokenized stream.
 */
std::unique_ptr<Token> tokenizeStream(std::istream &stream, std::set<std::string> &externs);

} // bf_compiler


#endif