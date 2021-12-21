#  ✨Logic Calculator

Program for calculating logical expressions generating truth tables

## Getting Started
### Installation
Simply open the source code in your favorite IDE (CLion, Visual Studios) and run!

Or if you prefer using terminal, cd into the cmake-build-debug folder and run using the executable

```bash
$ cd ~/LogicCalculator/cmake-build-debug
$ ./LogicCalculator
```

### Usage
After getting the prompt to input an expression, enter your logical expression using letters as variables and logical operators

This program supports logical conjunction, disjunction, implication, equality, and negation operators (&, |, ->, <->, !)

```
Enter Expression: a&b|(a->!c)
```

You will then be promoted to enter the truth values [T,F] for the operands previously entered
```
Enter Values [T,F]: 
   a: t
   b: f
   d: t
```

You will then be shown the result of the values that you entered, as well as a truth table generated using your expression!
```
Result: true

Truth Table: 
| a | d | b | a&b|(a&d) |
-------------------------
| T | T | T |     T     |
| T | T | F |     T     |
| T | F | T |     T     |
| T | F | F |     F     |
| F | T | T |     F     |
| F | T | F |     F     |
| F | F | T |     F     |
| F | F | F |     F     |
```

You can then enter 'quit' to quit the program, or enter another expression to continue

```
Enter 'quit' to quit
Enter Expression: 
```
## Lisence
Created entrely by me, Daniel Ryan, as a coding assignment for CS2353 at SMU 
