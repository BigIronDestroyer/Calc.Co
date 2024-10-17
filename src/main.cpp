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
    std::cout << "Welcom to Cocalc your go to quick calclulator!\n\n";

    // get equation form user
    std::string equation;
    std::cout << "Enter a Mathimatical Equation (! to quit): ";
    std::cin >> equation;

    while (equation != "!")
    {
        // return equation solution
        try
        {
            // solve the equation
            parse::do_calculations(equation);

            // get user input
            std::cout << "Enter a Mathimatical Equation (! to quit): ";
            std::cin >> equation;
        }
        catch (const std::runtime_error &e)
        {
            // catch divide by zero
            std::cerr << e.what() << '\n';
        }
    }

    return 0;
}