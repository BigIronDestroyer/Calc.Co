#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include "../include/tokenizer.hpp"

namespace tokenizer
{
    std::vector<Tokenizer::Token> Tokenizer::tokenize(const std::string &equation)
    {
        // initialize a vector of Token
        std::vector<Tokenizer::Token> tokens;

        // loop through equation stream
        for (std::string::size_type i = 0; i < equation.length(); i++)
        {
            // skip white space
            if (isspace(equation[i]))
            {
                continue;
            }
            // if the current element is a number or decimal
            else if (isdigit(equation[i]) || equation[i] == '.')
            {
                std::string number;
                // string stream
                // keeps track of a whole number
                std::stringstream ss;

                // while the current element is a number or decimal
                while (i < equation.length() && (isdigit(equation[i]) || equation[i] == '.'))
                {
                    // uses i then increments it after it has been used
                    ss << equation[i++];
                }
                // while loop goes untill i is not a number or decimal
                // we need to take a step back
                i--;
                // read what is in the string stream into numbers variable
                ss >> number;

                tokens.emplace_back(Tokenizer::Token(Tokenizer::TokenType::NUMBER, number));
            }
            // if the current index is an operators
            else if (equation[i] == '+' || equation[i] == '-' || equation[i] == '*' || equation[i] == '/' || equation[i] == '%')
            {
                std::string opp;

                // Check for '**' for exponentiation
                if (equation[i] == '*' && (i + 1 < equation.length()) && equation[i + 1] == '*')
                {
                    // Exponentiation
                    opp = "**";
                    // Skip the second '*'
                    i++;
                }
                else
                {
                    // Single operator
                    opp = equation[i];
                }

                // add operator to vector
                if (opp == "+")
                {
                    tokens.emplace_back(Tokenizer::TokenType::OPERATOR3, opp);
                }
                else if (opp == "-")
                {
                    tokens.emplace_back(Tokenizer::TokenType::OPERATOR3, opp);
                }
                else if (opp == "*")
                {
                    tokens.emplace_back(Tokenizer::TokenType::OPERATOR2, opp);
                }
                else if (opp == "/")
                {
                    tokens.emplace_back(Tokenizer::TokenType::OPERATOR2, opp);
                }
                else if (opp == "**")
                {
                    tokens.emplace_back(Tokenizer::TokenType::OPERATOR1, opp);
                }
                else if (opp == "%")
                {
                    tokens.emplace_back(Tokenizer::TokenType::OPERATOR2, opp);
                }
            }
            else if (equation[i] == '(' || equation[i] == ')')
            {
                tokens.emplace_back(Tokenizer::TokenType::PARENTHESES, std::string(1, equation[i]));
            }
            else
            {
                std::ostringstream oss;
                oss << "Unrecognized character in Equation '" << equation[i] << "'";
                throw std::runtime_error(oss.str());
            }
        }
        return tokens;
    }

    // print tokens(FOR DEBUGING ONLY)
    void Tokenizer::printTokens(const std::vector<Token> &tokens)
    {
        for (const auto &token : tokens)
        {
            std::cout << "Type: ";
            switch (token.type)
            {
            case TokenType::NUMBER:
                std::cout << "NUMBER";
                break;
            case TokenType::OPERATOR1:
                std::cout << "OPERATOR1";
                break;
            case TokenType::OPERATOR2:
                std::cout << "OPERATOR2";
                break;
            case TokenType::OPERATOR3:
                std::cout << "OPERATOR3";
                break;
            case TokenType::PARENTHESES:
                std::cout << "PARENTHESIS";
                break;
            }
            std::cout << ", Value: " << token.value << "\n";
        }
    }
}

// void do_calculations(std::string equation)
// {
//     int queues = parse_eq(equation);
//     int solution = 0;
//     bool is_first = true;
//     if (!queues.bool_error)
//     {
//         while (!queues.operators.empty())
//         {
//             // grab the top operator and remove it
//             std::string opp = queues.operators.front();
//             queues.operators.pop();
//             int x, y = 0;
//             // pop 2 number from the values stack for the first time
//             // grab the top number and pop it off to remove
//             if (is_first)
//             {
//                 x = queues.values.front();
//                 queues.values.pop();
//                 is_first = false;
//             }
//             else
//             {
//                 x = solution;
//             }
//             // y will always be popped from the stack
//             y = queues.values.front();
//             queues.values.pop();

//             // apply opperation
//             if (opp == "**")
//             {
//                 solution = calculate::exponent(x, y);
//             }
//             else
//             {
//                 solution = calculate::solve(opp[0], x, y);
//             }
//         }

//         std::cout << "Result: " << solution << std::endl;
//     }
//     else
//     {
//         std::cout << queues.err_msg << std::endl;
//     }
//}