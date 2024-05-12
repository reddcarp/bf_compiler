#include <cstdio>
#include <iostream>
#include <stdexcept>

#include "token.hpp"

namespace bf_compiler {

Token::Token(char t)
: token(t)
{}

StartToken::StartToken() : Token(' ') { }
Token* StartToken::addSegment(std::ostream &os) {
    return next_token.get();
}

IncrementIndexToken::IncrementIndexToken(std::set<std::string> &externs) : Token('>') {
    externs.emplace("increaseIndex");
}
Token* IncrementIndexToken::addSegment(std::ostream &os) {
    os << "mov rdi, " << repeated << "\n";
    os << "call increaseIndex" << "\n";

    return next_token.get();
}

DecrementIndexToken::DecrementIndexToken(std::set<std::string> &externs) : Token('<') {
    externs.emplace("decreaseIndex");
}
Token* DecrementIndexToken::addSegment(std::ostream &os) {
    os << "mov rdi, " << repeated << "\n";
    os << "call decreaseIndex" << "\n";

    return next_token.get();
}

IncrementDataToken::IncrementDataToken(std::set<std::string> &externs) : Token('+') {
    externs.emplace("dataArr");
    externs.emplace("dataIndex");
}
Token* IncrementDataToken::addSegment(std::ostream &os) {
    os << "addToData " << repeated << "\n";

    return next_token.get();
}

DecrementDataToken::DecrementDataToken(std::set<std::string> &externs) : Token('-') {
    externs.emplace("dataArr");
    externs.emplace("dataIndex");
}
Token* DecrementDataToken::addSegment(std::ostream &os) {
    os << "subFromData " << repeated << "\n";

    return next_token.get();
}

OutputDataToken::OutputDataToken(std::set<std::string> &externs) : Token('.') {
    externs.emplace("printData");
}
Token* OutputDataToken::addSegment(std::ostream &os) {
    for (int i = 0; i < repeated; i++) {
        os << "call printData" << "\n";
    }

    return next_token.get();
}

InputDataToken::InputDataToken(std::set<std::string> &externs) : Token(',') {
    externs.emplace("readData");
}
Token* InputDataToken::addSegment(std::ostream &os) {
    os << "call readData" << "\n";

    return next_token.get();
}

JmpIfZeroToken::JmpIfZeroToken(std::set<std::string> &externs) : Token('[') {
    externs.emplace("dataArr");
    externs.emplace("dataIndex");
}
Token* JmpIfZeroToken::addSegment(std::ostream &os) {
    os << "jmpIfDataZero " << jmpToLabel << "\n";
    os << jmpLabel << ":\n";

    return next_token.get();
}

JmpIfNotZeroToken::JmpIfNotZeroToken() : Token(']') {}
Token* JmpIfNotZeroToken::addSegment(std::ostream &os) {
    os << "jmpIfDataNotZero " << jmpToLabel << "\n";
    os << jmpLabel << ":\n";

    return next_token.get();
}

} // bf_compiler