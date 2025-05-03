#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <cctype>

RPN::RPN(){}

RPN::RPN(const RPN& other)
{
    result = other.result; 
}

RPN& RPN::operator=(const RPN& other)
{
    if(this != &other)
        result = other.result;
    return *this;
}

RPN::~RPN(){}

void RPN::apply_operations(char curr_tok)
{
    int a, b;
    if (result.size() < 2)
    {
        std::cerr << "Error: Not enough operands\n";
        return;
    }

    a = result.top();
    result.pop();
    b = result.top();
    result.pop();

    if (curr_tok == '+')
        result.push(b + a);
    else if (curr_tok == '-')
        result.push(b - a);
    else if (curr_tok == '*')
        result.push(b * a);
    else if (curr_tok == '/')
    {
        if (a == 0)
        {
            std::cerr << "Error: Division by zero\n";
            return;
        }
        result.push(b / a);
    }
}

void RPN::process_tokens(const std::string& input)
{
    std::string op = "+-*/";
    std::stringstream str(input);
    std::string token;
    std::string curr_tok;

    while (str >> token) 
    {
        curr_tok = token;
        if (curr_tok.size() == 1 && std::isdigit(curr_tok[0]))
            result.push(curr_tok[0] - '0');
        else if (curr_tok.size() == 1 && op.find(curr_tok[0]) != std::string::npos)
            apply_operations(curr_tok[0]);
        else
        {
            std::cerr << "Error: Invalid token\n";
            return;
        }
    }
    if (result.size() == 1)
        std::cout << result.top() << std::endl;
    else
        std::cerr << "Error: Invalid Expression\n";
}



