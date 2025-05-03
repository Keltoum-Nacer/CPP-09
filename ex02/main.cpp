#include"PmergeMe.hpp"

int main(int ac, char **av)
{
    PmergeMe seq;
    if(ac == 1)
    {
        std::cerr << "Usage: " << av[0] << " positive integers \n";
        return 1;
    }
    seq.check_input(av);
}
