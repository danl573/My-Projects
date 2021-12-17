//
// Created by Daniel Ryan on 12/6/21.
//

#include "Calculator.h"

Calculator::Calculator(const std::string& expr) {
    values.insert(std::pair<char, bool>('?', true)); //generic true char
    values.insert(std::pair<char, bool>('#', false)); //generic false char

    //Precedences of operators
    precedence.insert(std::pair<char, int>('<', 3));
    precedence.insert(std::pair<char, int>('-', 3));
    precedence.insert(std::pair<char, int>('&', 2));
    precedence.insert(std::pair<char, int>('|', 2));
    precedence.insert(std::pair<char, int>('!', 1));

    equation = expr;
}

int Calculator::ReadEquation() {

    std::cout << "\nEnter Values [T,F]: " << std::endl;
    std::stringstream line(equation);
    std::string val;
    char buffer;
    while(line >> buffer) {
        if(std::isalpha(buffer)) {
            if(!values.count(buffer)) {
                std::cout << "   " << buffer << ": ";
                std::cin >> val;
                bool b = false;
                if(val == "T" ||val == "true" || val == "t")
                    b = true;
                values.insert(std::pair<char, bool>(buffer, b));
                var.push_back(buffer);
            }
            output.push_back(buffer);
        }else if(isOperator(buffer)) {
            while((!opr.empty() && opr.top() != '(') &&(precedence.at(opr.top()) < precedence.at(buffer) ||
                                                        (precedence.at(opr.top()) == precedence.at(buffer) && buffer != '!'))) {
                output.push_back(opr.top());
                opr.pop();
            }
            opr.push(buffer);
            if(buffer == '-' || buffer == '<') {
                if(buffer == '<') {
                    line >> buffer;
                    if(buffer != '-') {
                        std::cout << "ERROR: Invalid input";
                        return 1;
                    }
                }
                line >> buffer;
                if(buffer != '>'){
                    std::cout << "ERROR: Invalid input";
                    return 1;
                }
            }
        } else if(buffer == '(')
            opr.push(buffer);
        else if(buffer == ')') {
            while(opr.top() != '(') {
                if(opr.empty()) {
                    std::cout << "ERROR: Mismatched parentheses" << std::endl;
                    return 1;
                }
                output.push_back(opr.top());
                opr.pop();
            }
            opr.pop();
        } else {
            std::cout << "ERROR: Invalid input";
            return 1;
        }
    }
    while(!opr.empty()) {
        if(opr.top() == '(') {
            std::cout << "ERROR: Mismatched parentheses" << std::endl;
            return 1;
        }
        output.push_back(opr.top());
        opr.pop();
    }


    std::string result = (solveEquation()) ? "true" : "false";
    std::cout << "Result: " << result << std::endl;

    return 0;
}

bool Calculator::solveEquation() {
    std::vector<char> outputCopy = output;
    while(outputCopy.size() > 1) {
        int i = 0;
        char op = ' ';
        for(; i < outputCopy.size(); i++) {
            if(isOperator(outputCopy[i])) {
                op = outputCopy[i];
                break;
            }
        }
        bool result = true;
        if(op == '&')
            result = performAND(outputCopy[i-2], outputCopy[i-1]);
        else if(op == '|')
            result = performOR(outputCopy[i-2], outputCopy[i-1]);
        else if(op == '!')
            result = (!values.at(outputCopy[i - 1]));
        else if(op == '-')
            result = performConditional(outputCopy[i-2], outputCopy[i-1]);
        else if(op == '<')
            result = performBiCon(outputCopy[i-2], outputCopy[i-1]);

        outputCopy[i] = (result) ? '?' : '#';
        outputCopy.erase(outputCopy.begin() + (i-2));
        if(op == '&' || op == '|')
            outputCopy.erase(outputCopy.begin() + (i-2));
    }
    if(outputCopy[0] == '?')
        return true;
    if(outputCopy[0] == '#')
        return false;
}

void Calculator::generateTruthTable() {
    std::cout << "\nTruth Table: " << std::endl;
    std::cout << "| ";
    int numSpaces = 2;
    std::vector<char> vars;
    for (auto &c: values) {
        if (c.first != '?' && c.first != '#') {
            std::cout << c.first << " | ";
            vars.push_back(c.first);
            numSpaces += 4;
        }
    }
    std::cout << equation << " |" << std::endl;
    numSpaces += equation.length() + 2;
    for (int i = 0; i < numSpaces; i++)
        std::cout << "-";
    std::cout << std::endl;

    std::string equationSpace;
    for (int i = 0; i < equation.length() / 2; i++)
        equationSpace += " ";

    int colsCount = pow(2, values.size() - 2);
    int rowCount = pow(2, values.size() - 3);
    int index = 0;

    for (int c = 0; c < colsCount; c++) {
        index = 0;
        std::cout << "| ";
        for (int r = rowCount; r > 0; r /= 2) {
            if ((c / r) % 2 == 0) {
                std::cout << "T | ";
                values.at(vars[index]) = true;
            } else {
                std::cout << "F | ";
                values.at(vars[index]) = false;
            }
            index++;
        }
        std::cout << equationSpace;
        (solveEquation()) ? std::cout << "T" : std::cout << "F";
        std::cout << equationSpace;
        if (equation.length() % 2 == 0)
            std::cout << "|" << std::endl;
        else
            std::cout << " |" << std::endl;

    }
}

bool Calculator::performAND(char a, char b) {
    if(values.at(a) && values.at(b))
        return true;
    return false;
}

bool Calculator::performOR(char a, char b) {
    if(values.at(a) || values.at(b))
        return true;
    return false;
}

bool Calculator::performConditional(char a, char b) {
    if(values.at(a) && !values.at(b))
        return false;
    return true;
}

bool Calculator::performBiCon(char a, char b) {
    if(values.at(a) == values.at(b))
        return true;
    return false;
}

bool Calculator::isOperator(char c) {
    return (c == '&' || c == '|' || c == '!' || c == '-' || c == '<');
}
