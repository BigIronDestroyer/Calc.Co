#include <iostream>
#include <sstream>
#include <queue>
#include <utility>

#include "../include/parse.hpp"
#include "../include/calculations.hpp"

namespace parse
{

    Result parse_eq(std::string equation)
    {
        // initialize result
        Result queues;

        // initialize as false for each new equation
        queues.bool_error = false;

        // loop through equation stream
        for (std::string::size_type i = 0; i < equation.length(); i++)
        {
            // skip white space
            if (isspace(equation[i]))
            {
                continue;
            }
            // if the current element is a number or decimal
            else if (isdigit(equation[i]) || equation[i] == '.')
            {
                // string stream
                // keeps track of a whole number
                std::stringstream ss;

                // while the current element is a number or decimal
                while (i < equation.length() && (isdigit(equation[i]) || equation[i] == '.'))
                {
                    // uses i then increments it after it has been used
                    ss << equation[i++];
                }
                // while loop goes untill i is not a number or decimal
                // we need to take a step back
                i--;
                int number;
                // read what is in the string stream into numbers variable
                ss >> number;
                queues.values.push(number);
            }
            // if the current index is an operators
            else if (equation[i] == '+' || equation[i] == '-' || equation[i] == '*' || equation[i] == '/' || equation[i] == '%')
            {
                std::string opps;

                // Check for '**' for exponentiation
                if (equation[i] == '*' && (i + 1 < equation.length()) && equation[i + 1] == '*')
                {
                    // Exponentiation
                    opps = "**";
                    // Skip the second '*'
                    i++;
                }
                else
                {
                    // Single operator
                    opps = equation[i];
                }

                // add operator to stack
                queues.operators.push(opps);
            }
            else
            {
                std::ostringstream oss;

                oss << "Unrecognized character in Equation '" << equation[i] << "'";

                queues.bool_error = true;
                queues.err_msg = oss.str();
                break;
            }
        }

        // plan for future: have a funtion that will check for errors in relation to parsing
        // if there isnt already an error
        if (!queues.bool_error)
        {
            // check for uneven number of operators vs values
            // there should always be always be one less operator than value
            int opp_len = queues.operators.size();
            int val_len = queues.values.size();

            if ((val_len - 1) != opp_len)
            {
                queues.bool_error = true;
                queues.err_msg = "Number of values do not match number of operators";
            }
        }

        return queues;
    }

    void do_calculations(std::string equation)
    {
        Result queues = parse_eq(equation);
        int solution = 0;
        bool is_first = true;
        if (!queues.bool_error)
        {
            while (!queues.operators.empty())
            {
                // grab the top operator and remove it
                std::string opp = queues.operators.front();
                queues.operators.pop();
                int x, y;
                // pop 2 number from the values stack for the first time
                // grab the top number and pop it off to remove
                if (is_first)
                {
                    x = queues.values.front();
                    queues.values.pop();
                    is_first = false;
                }
                else
                {
                    x = solution;
                }
                // y will always be popped from the stack
                y = queues.values.front();
                queues.values.pop();

                // apply opperation
                if (opp == "**")
                {
                    solution = calculate::exponent(x, y);
                }
                else
                {
                    solution = calculate::solve(opp[0], x, y);
                }
            }

            std::cout << "Result: " << solution << std::endl;
        }
        else
        {
            std::cout << queues.err_msg << std::endl;
        }
    }
}