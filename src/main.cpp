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
    std::cout << "Welcom to Cocalc, your go to quick calclulator!\n\n";

    // Create a buffer to hold the user input
    const int MAX_SIZE = 100;

    while (true)
    {
        // return equation solution
        try
        {
            // get equation form user
            char* equation = new char[MAX_SIZE];
            std::cout << "Enter a Mathimatical Equation (Q or q to quit): ";
            //cin only read till the first white space
            std::cin.getline(equation, MAX_SIZE);
            
            if (*equation == 'Q' || *equation == 'q'){
                break;
            } else {
                // parse the equation
                int result = parse::Parse(equation);
                printf("Output: %d\n", result);
            }

            // delete dynamically allocated memory after using it
            delete[] equation;

        }
        catch (const std::runtime_error &e)
        {
            // catch divide by zero
            std::cerr << e.what() << '\n';
        }
    }

    return 0;
}