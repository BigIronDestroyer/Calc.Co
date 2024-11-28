#include <iostream>
#include <sstream>
#include <queue>
#include <utility>

#include "../include/parse.hpp"
#include "../include/calculations.hpp"


/* parsing mechanisims for recersive decent parsing
Expression → Term { '+' Term | '-' Term }
Term       → Factor { '*' Factor | '/' Factor }
Factor     → number | '(' Expression ')'
*/

namespace parse
{   
    //& makes sure that the pointer modified inside the function applies outside of it
    int parseFactor(const char*& x){
        //parse numbers and parentheses
        // if the current element is a number or decimal
        if (*x >= '0' && *x <= '9'){
            return *x++ - '0'; //insures it is a valid number
        } else {
            std::ostringstream oss;
            oss << "Expected an integer but found '" << *x << "'";
            throw std::runtime_error(oss.str());
        }
    }

    int parseTerm(const char*& x){
        //parse multiplication division and modulo
        
        //get first number
        int prod1 = parseFactor(x);
        
        //while the current opperator is mul or div or mod
        while (*x == '*' || *x == '/' || *x == '%'){
            char opp = ' ';
            //check for which opperator
            if (*x == '*'){
                opp = '*';
            }else if (*x == '/'){
                opp = '/';
            }else if (*x == '%'){ 
                opp = '%';
            }

            //step over the opperator
            *x++;
            
            //get the next number
            int prod2 = parseFactor(x);
            
            //evaluate
            prod1 = calculate::solve(opp, prod1, prod2);
        }
        return prod1;
    }

    int parseExpression(const char*& x){
        //parse addition and subtraction
        
        //get the first number
        int fact1 = parseTerm(x);
        
        //while the current opperator is add or sub
        while (*x == '+' || *x == '-' ){
            char opp = ' ';
            //check for addition
            if (*x == '+'){
                opp = '+';
            }else if (*x == '-'){ // check for subtracqtion
                opp = '-';
            }

            //step over the opperator
            *x++;
            
            //get the next number
            int fact2 = parseTerm(x);
            
            //evaluate
            fact1 = calculate::solve(opp, fact1, fact2);
        }
        return fact1;
    }

    int Parse(const char* equation){
        int result = parseExpression(equation);
        return result;
    }
}