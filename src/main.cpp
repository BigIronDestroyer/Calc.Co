#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

#include "../include/ascii.hpp"
#include "../include/parser.hpp"
#include "../include/tokenizer.hpp"
#include "../include/calculations.hpp"

using namespace parser;
int main()
{
    // print a calulator and welcome message
    std::cout << ascii::logo();
    std::cout << "Welcome to CalcCo, your go-to quick calculator!\n\n";
    // initilaize parser
    Parser parser;

    while (true)
    {
        // return equation solution
        try
        {
            // get equation form user
            std::string equation;
            std::cout << "Enter a Mathematical Equation (Q or q to quit): ";
            // cin only read till the first white space
            std::getline(std::cin, equation);

            if (equation == "Q" || equation == "q")
            {
                printf("Goodbye!\n");
                break;
            }
            else
            {   
                //tokenize the equation
                Tokenizer tokenizer;
                std::vector<Tokenizer::Token> tokens = tokenizer.tokenize(equation);

                // parse and evaluate the equation
                long double result = parser.Parse(tokens);

                // if the result is ##.00 floor it to an int
                if (std::floor(result) == result)
                {
                    printf("Output: %ld\n", static_cast<long int>(result));
                }
                else
                {
                    printf("Output: %.3Lf\n", result);
                }
            }
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << e.what() << '\n';
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    return 0;
}
