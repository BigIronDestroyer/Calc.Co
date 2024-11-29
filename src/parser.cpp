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
Factor     → number | '(' Expression ')'
*/
using namespace tokenizer;
namespace parser{
    std::string resultTree;
    //& makes sure that the pointer modified inside the function applies outside of it
    int Parser::parseFactor(std::vector<Tokenizer::Token>::const_iterator& tokenItr, std::vector<Tokenizer::Token>::const_iterator& end){
        //parse numbers and parentheses

        //catches unfinished inputs
        if (tokenItr == end) {
            throw std::runtime_error("Incomplete input, unexpected end of input while parsing factor.");
        }

        // if the current element is a number or decimal
        // when working with pointers -> is used instead of .
        if (tokenItr->type == Tokenizer::TokenType::NUMBER){
            //turn string value into integer
            int value = std::stoi(tokenItr->value);
            //move to the next token            
            tokenItr++;
            
            return value;
        } 

        //handle parentheses
        if (tokenItr->type == Tokenizer::TokenType::PARENTHESES && tokenItr->value == "(") {
            tokenItr++; //step over the open parethese
            int result = parseExpression(tokenItr, end);
            if (tokenItr->value == ")"){
                tokenItr++; //step over close parethese
            }else if (tokenItr == end || tokenItr->type != Tokenizer::TokenType::PARENTHESES || tokenItr->value != ")"){
                //throws error if the parenthese is not closed
                throw std::runtime_error("Expected ')' but found something else");
            }
            return result;
        }
        
        // if there is no retrun there is an error
        std::ostringstream oss;
        oss << "Expected an integer or or '(' but found '" << tokenItr->value << "'";
        throw std::runtime_error(oss.str());
        
    }

    int Parser::parseTerm(std::vector<Tokenizer::Token>::const_iterator& tokenItr, std::vector<Tokenizer::Token>::const_iterator& end){
        //parse multiplication division and modulo
        
        //get first number
        int prod1 = parseFactor(tokenItr, end);
        
        //while the current opperator is mul or div or mod
        while (tokenItr != end && tokenItr->type == Tokenizer::TokenType::OPERATOR2){
            char opp = ' ';
            //check for which opperator
            if (tokenItr->value == "*"){
                opp = '*';
            }else if (tokenItr->value == "/"){
                opp = '/';
            }else if (tokenItr->value == "%"){ 
                opp = '%';
            }

            //step over the opperator
            tokenItr++;
            
            //get the next number
            int prod2 = parseFactor(tokenItr, end);
            
            //evaluate
            prod1 = calculate::solve(opp, prod1, prod2);
        }
        return prod1;
    }

    int Parser::parseExpression(std::vector<Tokenizer::Token>::const_iterator& tokenItr, std::vector<Tokenizer::Token>::const_iterator& end){
        //parse addition and subtraction
        
        //get the first number
        int fact1 = parseTerm(tokenItr, end);
        
        //while the current opperator is add or sub
        while (tokenItr != end && tokenItr->type == Tokenizer::TokenType::OPERATOR3){
            char opp = ' ';
            //check for addition
            if (tokenItr->value == "+"){
                opp = '+';
            }else if (tokenItr->value == "-"){ // check for subtracqtion
                opp = '-';
            }

            //step over the opperator
            tokenItr++;
            
            //get the next number
            int fact2 = parseTerm(tokenItr, end);
            
            //evaluate
            fact1 = calculate::solve(opp, fact1, fact2);
        }
        return fact1;
    }

    int Parser::Parse(const std::string equation){
        Tokenizer tokenizer;
        std::vector<Tokenizer::Token> tokens = tokenizer.tokenize(equation);
        //gets the begining and end of tokens as constants
        auto tokenItr = tokens.cbegin();
        auto end = tokens.cend();
        //parse and return value
        int result = parseExpression(tokenItr, end);
        return result;
    }
}