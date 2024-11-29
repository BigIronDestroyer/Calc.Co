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

        int Parse(const std::string equation);

    private:
        // functions for parsign numbers,adding, and multipling
        int parseFactor(std::vector<Tokenizer::Token>::const_iterator &tokenItr, std::vector<Tokenizer::Token>::const_iterator &end);
        int parseTerm(std::vector<Tokenizer::Token>::const_iterator &tokenItr, std::vector<Tokenizer::Token>::const_iterator &end);
        int parseExpression(std::vector<Tokenizer::Token>::const_iterator &tokenItr, std::vector<Tokenizer::Token>::const_iterator &end);
    };
}

#endif