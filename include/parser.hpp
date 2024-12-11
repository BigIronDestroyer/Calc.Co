#ifndef PARSE_HPP
#define PARSE_HPP

#include "../include/calculations.hpp"
#include "../include/tokenizer.hpp"
#include "../include/tree.hpp"

#include <vector>

using namespace tokenizer;
namespace parser
{
    class Parser
    {
    public:
        long double Parse(std::vector<Tokenizer::Token> tokens);

    private:
        // functions for parsign numbers,parentheses and operators
        tree::BinaryTree::Node *parseFactor(std::vector<Tokenizer::Token>::const_iterator &tokenItr, std::vector<Tokenizer::Token>::const_iterator &end, tree::BinaryTree *&Tree);
        tree::BinaryTree::Node *parseTerm(std::vector<Tokenizer::Token>::const_iterator &tokenItr, std::vector<Tokenizer::Token>::const_iterator &end, tree::BinaryTree *&Tree);
        tree::BinaryTree::Node *parseExpression(std::vector<Tokenizer::Token>::const_iterator &tokenItr, std::vector<Tokenizer::Token>::const_iterator &end, tree::BinaryTree *&Tree);
        void checkIsEvenParentheses(std::vector<Tokenizer::Token>::const_iterator &tokenItr, std::vector<Tokenizer::Token>::const_iterator &end);
    };
}

#endif