#include <iostream>
#include <stack>
#include "Calculator.h"


int main() {

    std::cout << "~~Welcome to the LOGIC CALCULATOR~~" << std::endl;
    std::cout << "        ==== by Daniel ====        " <<std::endl;

    std::cout << "How to use: " << std::endl;
    std::cout << "1. Enter the expression using variables (any letter, case sensitive) and\n";
    std::cout << "     logical AND, OR, NOT, Conditional, and Biconditional operators (&, |, !, ->, <->),\n"
                 "     ex. a&b|(a->d)\n     DO NOT INCLUDE SPACES" << std::endl;
    std::cout << "2. Press ENTER to submit expression" << std::endl;
    std::cout << "3. Enter the truth values (T,F) of the variables" << std::endl;
    std::cout << "4. Press ENTER to evaluate the expression" << std::endl;


    std::cout << "\n\nEnter 'quit' to quit" << std::endl;
    std::cout << "Enter Expression: ";
    std::string expr;
    int result = 0;
    std::cin >> expr;
    while(expr != "quit") {
        Calculator c(expr);
        result = c.ReadEquation();
        if(result == 0)
            c.generateTruthTable();
        else
            std::cout << "Please Enter valid expression" << std::endl;

        std::cout << "\n\nEnter 'quit' to quit" << std::endl;
        std::cout << "Enter Expression: ";
        std::cin >> expr;
    }

    std::cout << "Adios!!" << std::endl;

    return 0;
}
//(a<->(b|(c&a)))&(c|(b->e))