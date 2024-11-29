#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

#include "../include/ascii.hpp"
#include "../include/parser.hpp"
#include "../include/calculations.hpp"

using namespace parser;
int main()
{
    // print a calulator and welcome message
    std::cout << ascii::logo();
    std::cout << "Welcom to CalcCo, your go to quick calclulator!\n\n";
    // initilaize parser
    Parser parser;

    while (true)
    {
        // return equation solution
        try
        {
            // get equation form user
            std::string equation;
            std::cout << "Enter a Mathimatical Equation (Q or q to quit): ";
            // cin only read till the first white space
            std::getline(std::cin, equation);

            if (equation == "Q" || equation == "q")
            {
                break;
            }
            else
            {
                // parse the equation
                double result = parser.Parse(equation);

                // if the result is ##.00 floor it to an int
                if (std::floor(result) == result)
                {
                    printf("Output: %d\n", static_cast<int>(result));
                }
                else
                {
                    printf("Output: %.3f\n", result);
                }
            }
        }
        catch (const std::runtime_error &e)
        {
            // catch divide by zero
            std::cerr << e.what() << '\n';
        }
    }

    return 0;
}