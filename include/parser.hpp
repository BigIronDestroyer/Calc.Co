#ifndef PARSE_HPP
#define PARSE_HPP

#include "../include/calculations.hpp"
#include "../include/tokenizer.hpp"

using namespace tokenizer;
namespace parser
{
    class Parser
    {
    public:
        // Define the Result structure
        struct Result
        {
            // store numbers from equation
            std::queue<int> values;
            // store operatorss from
            std::queue<std::string> operators;
            bool bool_error;
            // store errors
            std::string err_msg;
        };

        double Parse(const std::string equation);

    private:
        // functions for parsign numbers,parentheses and operators
        double parseFactor(std::vector<Tokenizer::Token>::const_iterator &tokenItr, std::vector<Tokenizer::Token>::const_iterator &end);
        double parseTerm(std::vector<Tokenizer::Token>::const_iterator &tokenItr, std::vector<Tokenizer::Token>::const_iterator &end);
        double parseExpression(std::vector<Tokenizer::Token>::const_iterator &tokenItr, std::vector<Tokenizer::Token>::const_iterator &end);
        void checkIsEvenParentheses(std::vector<Tokenizer::Token>::const_iterator &tokenItr, std::vector<Tokenizer::Token>::const_iterator &end);
    };
}

#endif