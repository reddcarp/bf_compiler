#include <format>
#include <stack>

#include "tokenize.hpp"

namespace bf_compiler {

static std::unique_ptr<Token> createAndLinkJmpTokens(std::stack<JmpIfZeroToken *> &jpm_starts, std::string_view jmp_label) {
    auto jmp_start_token = jpm_starts.top();
    jpm_starts.pop();

    auto jmp_end = std::make_unique<JmpIfNotZeroToken>();
    jmp_end->jmpLabel = jmp_label;
    jmp_end->jmpToLabel = jmp_start_token->jmpLabel;
    jmp_start_token->jmpToLabel = jmp_end->jmpLabel;

    return jmp_end;
}

template <typename TokenCreate>
static void handleRepeatableToken(Token *&cur, char c, TokenCreate createToken) {
    static_assert(std::is_invocable_r_v<std::unique_ptr<Token>, TokenCreate>);
    if (cur->token == c) {
        cur->repeated += 1;
    }
    else {
        cur->next_token = createToken();
        cur = cur->next_token.get();
    }
}

std::unique_ptr<Token> tokenizeStream(std::istream &stream, std::set<std::string> &externs) {
    auto head = std::make_unique<StartToken>();
    Token *cur = head.get();
    std::stack<JmpIfZeroToken *> jpm_starts;

    char c;
    size_t i = 0;
    while (stream.get(c)) {
        switch(c) {
            case '<':
                handleRepeatableToken(cur, c, [&externs]() { return std::make_unique<DecrementIndexToken>(externs); });
                break;
            case '>':
                handleRepeatableToken(cur, c, [&externs]() { return std::make_unique<IncrementIndexToken>(externs); });
                break;
            case '+':
                handleRepeatableToken(cur, c, [&externs]() { return std::make_unique<IncrementDataToken>(externs); });
                break;
            case '-':
                handleRepeatableToken(cur, c, [&externs]() { return std::make_unique<DecrementDataToken>(externs); });
                break;
            case '.':
                handleRepeatableToken(cur, c, [&externs]() { return std::make_unique<OutputDataToken>(externs); });
                break;
            case ',':
                cur->next_token = std::make_unique<InputDataToken>(externs);
                cur = cur->next_token.get();
                break;
            case '[':
                cur->next_token = std::make_unique<JmpIfZeroToken>(externs);
                cur = cur->next_token.get();
                cur->jmpLabel = std::format(".jmp_{}", i);
                jpm_starts.push(static_cast<JmpIfZeroToken *>(cur));
                break;
            case ']':
                if (jpm_starts.empty()) {
                    throw std::format_error("Error: missing corresponding `[`");
                }

                cur->next_token = createAndLinkJmpTokens(jpm_starts, std::format(".jmp_{}", i));
                cur = cur->next_token.get();
                break;
            default:
                i--; // Decrement the counter to account for the character that was not processed
                break;
        }
        i++;
    }

    if (!jpm_starts.empty()) {
        throw std::format_error("Error: missing corresponding `]`");
    }

    return head;
}

} // bf_compiler