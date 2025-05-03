#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other)
{
    vec = other.vec;
    deq = other.deq;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        vec = other.vec;
        deq = other.deq;
    }
    return *this;
}
PmergeMe::~PmergeMe() {}

int PmergeMe::check_input(char **av)
{
    int i = 1;
    int nb;
    while (av[i])
    {
        std::string arg(av[i]);
        for (size_t j = 0; j < arg.length(); ++j)
        {
            if (!isdigit(arg[j]))
            {
                std::cerr << "Error\n";
                return 0;
            }
        }
        std::stringstream ss(arg);
        ss >> nb;
        vec.push_back(nb);
        deq.push_back(nb);
        i++;
    }
    std::cout << "Before : ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    sort_vector(vec);
    sort_deque(deq);
    return 1;
}

void PmergeMe::sort_vector(std::vector<int> &nb)
{
    clock_t start = clock();
    int a, b;
    std::vector<int>largest;
    std::vector<int>lowest;
    std::vector<int>sorted_vec;
    
    for(size_t i = 0; i + 1 < nb.size(); i += 2)
    {
        a = nb.at(i);
        b = nb.at(i + 1);
        largest.push_back(std::max(a, b));
        lowest.push_back(std::min(a, b));
    }
    if(largest.size() < 1)
        return;
    sort_vector(largest);
    sorted_vec = largest;
    if (nb.size() % 2 != 0)
        lowest.push_back(nb.back());
    for(std::vector<int>::size_type i = 0; i < lowest.size(); i++)
    {
        std::vector<int>::iterator it;
        it = std::lower_bound(sorted_vec.begin(), sorted_vec.end(), lowest[i]);
        sorted_vec.insert(it, lowest[i]);
    }
    if(sorted_vec.size() == vec.size())
    {
        std::cout << "After : ";
        std::copy(sorted_vec.begin(), sorted_vec.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;   
        clock_t end = clock();
        double elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1e6; // convert to microseconds

        std::cout << "Time to process a range of " << sorted_vec.size() << " elements with std::vector : " << std::fixed << std::setprecision(5)
                << elapsed_time << " us" << std::endl;
    }
    nb = sorted_vec;
}

void PmergeMe::sort_deque(std::deque<int> &nb)
{
    clock_t start = clock();
    int a, b;
    std::deque<int>largest;
    std::deque<int>lowest;
    std::deque<int>sorted_deq;

    for(size_t i = 0; i + 1 < nb.size(); i += 2)
    {
        a = nb.at(i);
        b = nb.at(i + 1);
        largest.push_back(std::max(a, b));
        lowest.push_back(std::min(a, b));
    }
    if (largest.size() < 1)
        return;
    sort_deque(largest);
    sorted_deq = largest;
    if (nb.size() % 2 != 0)
        lowest.push_back(nb.back());
    for(size_t i = 0; i < lowest.size(); i++)
    {
        std::deque<int>::iterator it;
        it = std::lower_bound(sorted_deq.begin(), sorted_deq.end(), lowest[i]);
        sorted_deq.insert(it, lowest[i]);
    }
    nb = sorted_deq;
    if (sorted_deq.size() == deq.size())
    {
        clock_t end = clock();
        double elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1e6;
        std::cout << "Time to process a range of " << sorted_deq.size() << " elements with std::deque : " << std::fixed << std::setprecision(5)
                << elapsed_time << " us" << std::endl;
    }
}
