#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

#include "../include/ascii.hpp"
#include "../include/parse.hpp"
#include "../include/calculations.hpp"

int main()
{
    // print a calulator and welcome message
    std::cout << ascii::logo();
    std::cout << "Welcome to Cocalc, your go-to quick calculator!\n\n";


    while (true)
    {
        // return equation solution
        try
        {
            // get equation form user
            std::string equation;
            std::cout << "Enter a Mathematical Equation (! to quit): ";
            //cin only read till the first white space
            std::getline(std::cin, equation);
            
            if (equation == "!"){
                break;
            } else {
            // solve the equation
            parse::do_calculations(equation);
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
