#ifndef PARSE_HPP
#define PARSE_HPP

#include "../include/calculations.hpp"
#include <queue>

namespace parse
{
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

   

    int Parse(const char* equation);
    //functions for parsign numbers,adding, and multipling
    int parseFactor(char*& x);
    int parseExpresion(const char*& x);
    int parseTerm(const char*& x);
}

#endif