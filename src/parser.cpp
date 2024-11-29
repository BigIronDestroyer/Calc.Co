#include <iostream>
#include <sstream>
#include <queue>
#include <utility>
#include <vector>

#include "../include/parser.hpp"
#include "../include/tokenizer.hpp"
#include "../include/calculations.hpp"

/* parsing mechanisims for recersive decent parsing
this also helps to execute the order of precedence
Expression → Term { '+' Term | '-' Term }
Term       → Factor { '*' Factor | '/' Factor | '%' Factor }
Factor     → number | '(' Expression ')' | - Factor | + Factor
*/
using namespace tokenizer;
namespace parser
{
    std::string resultTree;
    //& makes sure that the pointer modified inside the function applies outside of it
    double Parser::parseFactor(std::vector<Tokenizer::Token>::const_iterator &tokenItr, std::vector<Tokenizer::Token>::const_iterator &end)
    {
        // parse numbers and parentheses

        // catches unfinished inputs
        if (tokenItr == end)
        {
            throw std::runtime_error("Error: Incomplete input, unexpected end of input while parsing factor.");
        }

        // if the current element is a number or decimal
        // when working with pointers -> is used instead of .
        if (tokenItr->type == Tokenizer::TokenType::NUMBER)
        {
            // turn string value into dopuble
            double value = std::stod(tokenItr->value);
            // move to the next token
            tokenItr++;

            return value;
        }

        // handle parentheses
        if (tokenItr->type == Tokenizer::TokenType::PARENTHESES && tokenItr->value == "(")
        {
            tokenItr++; // step over the open parethese
            double result = parseExpression(tokenItr, end);
            if (tokenItr->type == Tokenizer::TokenType::PARENTHESES && tokenItr->value == ")")
            {
                tokenItr++; // step over close parethese
            }
            else
            {
                // throws error if the parenthese is not closed
                throw std::runtime_error("Error: Expected ')' but found something else");
            }
            return result;
        }

        // handle unary operators + -
        if (tokenItr->type == Tokenizer::TokenType::OPERATOR3)
        {
            std::string tokenValue = tokenItr->value;
            tokenItr++;

            // check for missing opperand
            if (tokenItr != end && tokenItr->value == ")")
            {
                throw std::invalid_argument("Error: Missing Operand");
            }

            if (tokenValue == "+")
            {
                double factor = parseFactor(tokenItr, end);
                return factor;
            }
            else if (tokenValue == "-")
            {
                // negeate the next factor
                double factor = parseFactor(tokenItr, end);
                return -(factor);
            }
        }

        // if there is no retrun there is an error
        std::ostringstream oss;
        oss << "Expected an integer or or '(' but found '" << tokenItr->value << "'";
        throw std::runtime_error(oss.str());
    }

    double Parser::parseTerm(std::vector<Tokenizer::Token>::const_iterator &tokenItr, std::vector<Tokenizer::Token>::const_iterator &end)
    {
        // parse multiplication division and modulo and exponents

        // get first sequece of multiplication division and modulo
        double prod1 = parseFactor(tokenItr, end);

        // while the current opperator is exponents
        while (tokenItr != end && tokenItr->type == Tokenizer::TokenType::OPERATOR1)
        {
            // step over the opperator
            tokenItr++;

            // get first sequece of multiplication division and modulo
            double prod2 = parseFactor(tokenItr, end);

            // evaluate
            prod1 = calculate::exponent(prod1, prod2);
        }

        // while the current opperator is mul or div or mod
        while (tokenItr != end && tokenItr->type == Tokenizer::TokenType::OPERATOR2)
        {
            char opp = ' ';
            // check for which opperator
            if (tokenItr->value == "*")
            {
                opp = '*';
            }
            else if (tokenItr->value == "/")
            {
                opp = '/';
            }
            else if (tokenItr->value == "%")
            {
                opp = '%';
            }

            // step over the opperator
            tokenItr++;

            // get first sequece of multiplication division and modulo
            double prod2 = parseFactor(tokenItr, end);

            // evaluate
            prod1 = calculate::solve(opp, prod1, prod2);
        }
        return prod1;
    }

    double Parser::parseExpression(std::vector<Tokenizer::Token>::const_iterator &tokenItr, std::vector<Tokenizer::Token>::const_iterator &end)
    {
        // parse addition and subtraction

        // get the first number
        double fact1 = parseTerm(tokenItr, end);

        // while the current opperator is add or sub
        while (tokenItr != end && tokenItr->type == Tokenizer::TokenType::OPERATOR3)
        {
            char opp = ' ';
            // check for addition
            if (tokenItr->value == "+")
            {
                opp = '+';
            }
            else if (tokenItr->value == "-")
            { // check for subtracqtion
                opp = '-';
            }

            // step over the opperator
            tokenItr++;

            // check for invalid opperand sequence
            if (tokenItr != end && tokenItr->value == ")")
            {
                throw std::invalid_argument("Error: Invalid Operator Sequence");
            }

            // get the next number
            double fact2 = parseTerm(tokenItr, end);

            // evaluate
            fact1 = calculate::solve(opp, fact1, fact2);
        }
        return fact1;
    }

    void Parser::checkIsEvenParentheses(std::vector<Tokenizer::Token>::const_iterator &tokenItr, std::vector<Tokenizer::Token>::const_iterator &end)
    {
        int LParenthese = 0;
        while (tokenItr != end)
        {
            if (tokenItr->value == "(")
            {
                // there is an open parentheses
                LParenthese++;
            }
            else if (tokenItr->value == ")")
            {
                // there is a closed parentheses
                LParenthese--;
            }
            // go to the next token
            tokenItr++;
            /*
            there should be an even number of parenthese
            the thought behind this is that since they are
            even the number of left paretheses minus the number
            of right parentheses should be 0
            */
        }

        // throw error if they are unbalanced
        if (LParenthese != 0)
        {
            throw std::runtime_error("Error: The parentheses are not properly matched");
        }
    }

    double Parser::Parse(const std::string equation)
    {
        Tokenizer tokenizer;
        std::vector<Tokenizer::Token> tokens = tokenizer.tokenize(equation);
        // gets the begining and end of tokens as constants
        auto tokenItr = tokens.cbegin();
        auto end = tokens.cend();
        // will be used for the checking parentheses function
        auto tokenItrCopy = tokenItr;
        auto endCopy = end;
        // parse and return value
        checkIsEvenParentheses(tokenItrCopy, endCopy);
        double result = parseExpression(tokenItr, end);
        if (tokenItr != end)
        {
            throw std::runtime_error("Error: Parseing unexpectedly end while the equations was not fully processed");
        }
        return result;
    }
}