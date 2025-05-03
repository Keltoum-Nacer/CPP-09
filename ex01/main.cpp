#include "RPN.hpp"

int main(int ac, char **av)
{
    RPN rpn;
    if(ac != 2)
    {
        std::cerr << "Error: ./RPN <RPN expression> \n";
        return 1;
    }
    rpn.process_tokens(av[1]);
}
