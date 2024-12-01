#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <cmath> // For pow function

#include "../include/calculations.hpp"

namespace calculate
{
    double solve(std::string opp, double x, double y)
    {
        if (opp == "+")
        {
            return x + y;
        }

        if (opp == "-")
        {
            return x - y;
        }

        if (opp == "/"){
            if (y == 0)
            {
                throw std::runtime_error("Error: Divition by Zero");
            }
            return x / y;
        }
        if (opp == "*")
        {
            return x * y;
        }
        if (opp == "%")
        {
            if (y == 0){
                throw std::runtime_error("Error: Modulo by zero");
            }

            //fmod allows for modulo with doubles
            return std::fmod(x, y); 
        }

        if (opp == "**")
        {
            //pow allows for expomnents with doubles
            return std::pow(x, y);
        }

        // If none of the cases match, you need to handle this
        std::ostringstream oss;
        oss << "Error: Unsupported Operator '" << opp << "'";
        throw std::invalid_argument(oss.str());
    }
}
