#include <iostream>
#include <sstream>
#include <queue>
#include <utility>
#include <vector>

#include "../include/parser.hpp"
#include "../include/tokenizer.hpp"
#include "../include/calculations.hpp"
#include "../include/tree.hpp"

/* parsing mechanisims(gramar) for recersive decent parsing
this also helps to execute the order of precedence
Expression → Term { '+' Term | '-' Term }
Term       → Factor { '*' Factor | '/' Factor | '%' Factor }
Factor     → number | '(' Expression ')' | - Factor | + Factor
*/
using namespace tokenizer;
namespace parser
{
    //& makes sure that the pointer modified inside the function applies outside of it
    tree::BinaryTree::Node *Parser::parseFactor(std::vector<Tokenizer::Token>::const_iterator &tokenItr, std::vector<Tokenizer::Token>::const_iterator &end, tree::BinaryTree *&Tree)
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
            // createNode
            tree::BinaryTree::Node *newNode = Tree->createNode(tokenItr->value);
            // move to the next token
            tokenItr++;
            if (tokenItr->type == Tokenizer::TokenType::PARENTHESES && tokenItr->value == "("){
                throw std::runtime_error("Error: Missing Operator");
            }

            return newNode;
        }

        // handle parentheses
        if (tokenItr->type == Tokenizer::TokenType::PARENTHESES && tokenItr->value == "(")
        {
            tokenItr++; // step over the open parethese
            // create a newNode
            tree::BinaryTree::Node *newNode = parseExpression(tokenItr, end, Tree);
            if (tokenItr->type == Tokenizer::TokenType::PARENTHESES && tokenItr->value == ")")
            {
                tokenItr++; // step over close parethese
            }
            else
            {
                // throws error if the parenthese is not closed
                throw std::runtime_error("Error: Expected ')' but found something else");
            }
            return newNode;
        }

        // handle unary operators + -
        if (tokenItr->type == Tokenizer::TokenType::OPERATOR3)
        {
            std::string unaryOp = tokenItr->value;
            //step over unary operator
            tokenItr++;

            // check for missing opperand
            if (tokenItr != end && tokenItr->value == ")")
            {
                throw std::invalid_argument("Error: Missing Operand");
            }

           
            tree::BinaryTree::Node *newNode = parseFactor(tokenItr, end, Tree);
            
            //create a unaryOp node
            tree::BinaryTree::Node *unaryNode = Tree->createNode(unaryOp);
            unaryNode->left = nullptr;
            unaryNode->right = newNode;

            return unaryNode;
        }

        if (tokenItr->type == Tokenizer::TokenType::OPERATOR2 || tokenItr->type == Tokenizer::TokenType::OPERATOR2){
            throw std::invalid_argument("Error: Missing Operand");
        }

        // if there is no retrun there is an error
        std::ostringstream oss;
        oss << "Expected an integer or or '(' but found '" << tokenItr->value << "'";
        throw std::runtime_error(oss.str());
    }

    tree::BinaryTree::Node *Parser::parseTerm(std::vector<Tokenizer::Token>::const_iterator &tokenItr, std::vector<Tokenizer::Token>::const_iterator &end, tree::BinaryTree *&Tree)
    {
        // parse multiplication division and modulo and exponents

        // get first sequece of multiplication division and modulo
        // tree::BinaryTree::Node* left
        tree::BinaryTree::Node *left = parseFactor(tokenItr, end, Tree);

        // while the current opperator is exponents
        while (tokenItr != end && tokenItr->type == Tokenizer::TokenType::OPERATOR1)
        {
            // step over the opperator
            // createNode
            tree::BinaryTree::Node *opp = Tree->createNode(tokenItr->value);

            // move to the next token
            tokenItr++;

            // get first sequece of multiplication division and modulo
            // create right node
            tree::BinaryTree::Node *right = parseFactor(tokenItr, end, Tree);

            // evaluate
            // insertNode
            left = Tree->insertNode(opp, left, right);
        }

        // while the current opperator is mul or div or mod
        while (tokenItr != end && tokenItr->type == Tokenizer::TokenType::OPERATOR2)
        {
            // create operator node
            tree::BinaryTree::Node *opp = Tree->createNode(tokenItr->value);

            // step over the opperator
            tokenItr++;

            // get first sequece of multiplication division and modulo
            tree::BinaryTree::Node *right = parseFactor(tokenItr, end, Tree);

            // evaluate
            // insertnode
            left = Tree->insertNode(opp, left, right);
        }

        return left;
    }
    tree::BinaryTree::Node *Parser::parseExpression(std::vector<Tokenizer::Token>::const_iterator &tokenItr, std::vector<Tokenizer::Token>::const_iterator &end, tree::BinaryTree *&Tree)
    {
        // parse addition and subtraction

        // get the first number
        // create left node
        tree::BinaryTree::Node *left = parseTerm(tokenItr, end, Tree);

        // while the current opperator is add or sub
        while (tokenItr != end && tokenItr->type == Tokenizer::TokenType::OPERATOR3)
        {
            tree::BinaryTree::Node *opp = Tree->createNode(tokenItr->value);

            // step over the opperator
            tokenItr++;

            // check for invalid opperand sequence
            if (tokenItr != end && tokenItr->value == ")")
            {
                throw std::invalid_argument("Error: Invalid Operator Sequence");
            }

            // get the next number
            //// tree::BinaryTree::Node* right
            tree::BinaryTree::Node *right = parseTerm(tokenItr, end, Tree);

            // evaluate
            // insertNode(node, opp, fact1, fact2)
            left = Tree->insertNode(opp, left, right);
        }
        return left;
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

    long double Parser::Parse(std::vector<tokenizer::Tokenizer::Token> tokens)
    {
        // gets the begining and end of tokens as constants
        auto tokenItr = tokens.cbegin();
        auto end = tokens.cend();
        // will be used for the checking parentheses function
        auto tokenItrCopy = tokenItr;
        auto endCopy = end;
        // parse and return value
        checkIsEvenParentheses(tokenItrCopy, endCopy);
        tree::BinaryTree Tree = tree::BinaryTree();
        tree::BinaryTree *treePtr = &Tree;
        tree::BinaryTree::Node *resultTree = parseExpression(tokenItr, end, treePtr);
        if (tokenItr != end)
        {
            throw std::runtime_error("Error: Parsing unexpectedly ended while the equation was not fully processed");
        }

        //evaluate equation
       long double result = Tree.evaluateTree(resultTree);

        return result;
    }
}