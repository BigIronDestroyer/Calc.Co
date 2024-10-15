#ifndef PARSE_HPP
#define PARSE_HPP

#include "../include/calculations.hpp"
#include <queue>


namespace parse{
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

    Result parse_eq(std::string equation);
    void do_calculations(std::string equation);
}


#endif