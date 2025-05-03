#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include<iostream>
#include<vector>
#include<deque>
#include<iterator>
#include<algorithm>
#include<sstream>
#include<ctime>
#include<iomanip>

class PmergeMe
{
    private:
        std::vector<int> vec;
        std::deque<int> deq;
    public:
        PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();
        int check_input(char **av);
        void sort_vector(std::vector<int> &nb);
        void sort_deque(std::deque<int> &nb);
};

#endif
