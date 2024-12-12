
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
#include <vector>
#include "../include/calculations.hpp"

namespace tokenizer
{

    class Tokenizer
    {
    public:
        // defines token types
        // OPERATOR1 refers to **
        // OPERATOR2 refers to * / %
        // OPERATOR3 refers to + -
        enum class TokenType
        {
            NUMBER,
            OPERATOR1,
            OPERATOR2,
            OPERATOR3,
            PARENTHESES
        };

        // structure of a token
        struct Token
        {
            TokenType type;
            std::string value;

            // initialize
            Token(TokenType t, const std::string &v) : type(t), value(v) {}
        };

        std::vector<Token> tokenize(const std::string &expression);

    private:
        void printTokens(const std::vector<Token> &tokens);
    };
}
#endif
