#ifndef RPN_HPP
#define RPN_HPP

#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<sstream>
#include<cctype>

class RPN
{
    private:
        std::stack<int> result;
    public:
        RPN();
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);
        ~RPN();
        void apply_operations(char curr_tok);
        void process_tokens(const std::string& input);
};

#endif
