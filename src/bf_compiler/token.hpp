#ifndef BF_COMPILER_TOKEN_HPP
#define BF_COMPILER_TOKEN_HPP

#include <set>
#include <iostream>
#include <memory>

namespace bf_compiler {

// Abstract class

class Token {
 public:
    explicit Token(char t);
    virtual ~Token() = default;

    virtual Token* addSegment(std::ostream &os) = 0;

    std::unique_ptr<Token> next_token = nullptr; /* A pointer to the next token. */
    size_t repeated = 1; /* The number of times the token is repeated. */
    const char token;   /* The token character. */
    std::string jmpLabel; /* The label for the jump token. */
    std::string jmpToLabel; /* The label for the end of the jump token. */
};

// ==============================================================

// Implemented Tokens

// Special Token, used to represent the beginning of the token linked-list
class StartToken : public Token {
 public:
    StartToken();
    Token* addSegment(std::ostream &os) final;
};

// BF Token: `>`
class IncrementIndexToken : public Token {
 public:
    IncrementIndexToken(std::set<std::string> &externs);
    Token* addSegment(std::ostream &os) final;
};

// BF Token: `<`
class DecrementIndexToken : public Token {
 public:
    DecrementIndexToken(std::set<std::string> &externs);
    Token* addSegment(std::ostream &os) final;
};

// BF Token: `+`
class IncrementDataToken : public Token {
 public:
    IncrementDataToken(std::set<std::string> &externs);
    Token* addSegment(std::ostream &os) final;
};

// BF Token: `-`
class DecrementDataToken : public Token {
 public:
    DecrementDataToken(std::set<std::string> &externs);
    Token* addSegment(std::ostream &os) final;
};

// BF Token: '.'
class OutputDataToken : public Token {
 public:
    OutputDataToken(std::set<std::string> &externs);
    Token* addSegment(std::ostream &os) final;
};

// BF Token: `,`
class InputDataToken : public Token {
 public:
    InputDataToken(std::set<std::string> &externs);
    Token* addSegment(std::ostream &os) final;
};

// BF Token: `[`
class JmpIfZeroToken : public Token {
 public:
    JmpIfZeroToken(std::set<std::string> &externs);
    Token* addSegment(std::ostream &os) final;
};

// BF Token: `]`
class JmpIfNotZeroToken : public Token {
 public:
    JmpIfNotZeroToken();
    Token* addSegment(std::ostream &os) final;
};
// ==============================================================

} // bf_compiler

#endif