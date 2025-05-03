#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    this->data = other.data;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if(this != &other)
        this->data = other.data;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

int BitcoinExchange::toInt(const std::string& str) {
    std::stringstream ss(str);
    int result;
    ss >> result;
    return result;
}

double BitcoinExchange::toDouble(const std::string& str) {
    std::stringstream ss(str);
    double result;
    ss >> result;
    return result;
}

bool BitcoinExchange::valid_date(std::string &date)
{
    int year, month, day;
    if (date.empty())
        return 0;
    if (date.size() != 10)
        return 0;
    for(int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
        {
            if(date[i] != '-')
                return 0;
        }
        else
        {
            if(!isdigit(date[i]))
                return 0;
        }
    }
    year = toInt(date.substr(0, 4));
    month = toInt(date.substr(5, 2));
    day = toInt(date.substr(8, 2));
    if (month > 12 || month < 1)
        return 0;
    if (day > 31 || day < 1)
        return 0;
    return 1;
}

bool BitcoinExchange::valid_price(std::string &price)
{
    if (price.empty())
        return 0;
    bool flg = 0;
    for (std::string::size_type i = 0; i < price.size(); i++)
    {
        if(price[i] == '.')
        {
            if (flg)
                return 0;
            flg = 1;
        }
        else if(!isdigit(price[i]) && price[i] != '-')
        {
            std::cerr << "here\n";
            return 0;
        }
    }
    return 1;
}

int BitcoinExchange::parse_line(std::string line)
{
    std::stringstream dp(line);
    std::string date, price;
    std::getline(dp >> std::ws, date, ',');
    std::getline(dp >> std::ws, price, ',');
    if (!valid_date(date) || !valid_price(price))
    {
        std::cerr << "Error: bad input => " << line <<"\n";
        return 0;
    }
    data.insert(std::pair<std::string, double>(date, toDouble(price)));
    return 1;
}

void BitcoinExchange::read_database()
{
    std::ifstream file;
    std::string line;
    bool empty = 1;
    file.open("data.csv");
    if (!file)
    {
        std::cerr<<"Error in opening file!\n";
        return;
    }
    bool top = 1;
    while(getline(file, line))
    {
        if (top)
        {
            if (line.find("date,exchange_rate") != std::string::npos)
            {
                top = 0;
                continue;
            }
        }
        empty = 0;
        if(!parse_line(line))
            return;
    }
    if (empty)
        std::cerr<< "Error: data file is empty!\n";
}

double BitcoinExchange::get_price(std::string& date, double val)
{
    if(data.empty())
    {
        std::cerr << "Error: no data available" << std::endl;
        return -1;
    }
    std::map<std::string, double>::iterator it;
    it = data.lower_bound(date);
    if (it == data.end())
    {
        it --;
        return(it->second * val);
    }
    if(it != data.end() && it->first == date)
        return(it->second * val);
    if(it == data.begin())
    {
        std::cerr << "Error: no previous date exists\n";
        return -1;
    }
    it--;
    return(it->second * val);
}

void BitcoinExchange::read_input(std::string input)
{
    std::ifstream in_file;
    std::string line;
    in_file.open(input.c_str());
    if(!in_file)
    {
        std::cerr<<"Error in opening file!\n";
        return;
    }
    bool top = 1;
    while(getline(in_file, line))
    {
        if (top)
        {
            if (line.find("date | value") != std::string::npos)
            {
                top = 0;
                continue;
            }
        }
        double val;
        std::stringstream dp(line);
        std::string date, price;
        std::getline(dp, date, '|');
        std::getline(dp, price, '|');
        date.erase(0, date.find_first_not_of(" \t\r\n"));
        date.erase(date.find_last_not_of(" \t\r\n") + 1);
        price.erase(0, price.find_first_not_of(" \t\r\n"));
        price.erase(price.find_last_not_of(" \t\r\n") + 1);
        if (!valid_date(date) || !valid_price(price))
        {
            std::cerr << "Error: bad input => " << line <<"\n";
            continue;
        }
        val = toDouble(price);
        if(val < 0)
        {
            std::cerr << "Error: not a positive number!\n";
            continue;
        }
        else if (val > 1000)
        {
            std::cerr << "Error: number too large!\n";
            continue;
        }
        double result = get_price(date, val);
        if(result != -1)
            std::cout << date << " => " << val << " = " << result << std::endl;
    }
}
