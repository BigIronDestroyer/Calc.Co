#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <cmath> // For pow function

#include "../include/calculations.hpp"

namespace calculate
{
    double solve(char opp, double x, double y)
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
            // doubles have to be cast into int because C does not support modulos with doubles
            return static_cast<int>(x) % static_cast<int>(y);
        default:
            // If none of the cases match, you need to handle this
            std::ostringstream oss;
            oss << "Expected an opperator but found '" << opp << "'";
            throw std::runtime_error(oss.str());
        }
    }

    double exponent(int x, int y)
    {
        return pow(x, y);
    }

}
