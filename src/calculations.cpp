#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <cmath> // For pow function

#include "../include/calculations.hpp"

namespace calculate
{
    int solve(char opp, int x, int y)
    {
        switch (opp)
        {
        case '+':
            return x + y;
        case '-':
            return x - y;
        case '/':
            if (y == 0)
            {
                throw std::runtime_error("Error: Divition by Zero");
            }
            return x / y;
        case '*':
            return x * y;
        case '%':
            return x % y;
        default:
            // If none of the cases match, you need to handle this
            std::ostringstream oss;
            oss << "Expected an opperator but found '" << opp << "'";
            throw std::runtime_error(oss.str());
        }
    }

    int exponent(int x, int y)
    {
        return pow(x, y);
    }

}
