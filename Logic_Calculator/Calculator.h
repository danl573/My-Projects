#ifndef LOGICCALCULATOR_CALCULATOR_H
#define LOGICCALCULATOR_CALCULATOR_H

#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <vector>
#include <set>
#include <unordered_map>


class Calculator {
private:
    std::unordered_map<char, bool> values;
    std::unordered_map<char, int> precedence;
    std::string equation;

    std::vector<char> output;
    std::vector<char> var;
    std::stack<char> opr;

public:
    Calculator(const std::string&);
    int ReadEquation();
    bool solveEquation();
    bool performAND(char, char);
    bool performOR(char, char);
    bool performConditional(char, char);
    bool performBiCon(char, char);
    void generateTruthTable();

    bool isOperator(char);
};


#endif //LOGICCALCULATOR_CALCULATOR_H
