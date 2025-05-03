#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cctype>
#include<map>

class BitcoinExchange
{
    private:
        std::map<std::string, double> data;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange& operator=(const BitcoinExchange &other);
        ~BitcoinExchange();
        int toInt(const std::string& str);
        double toDouble(const std::string& str);
        void read_database();
        int parse_line(std::string line);
        bool valid_price(std::string &price);
        bool valid_date(std::string &date);
        void read_input(std::string input);
        double get_price(std::string& date, double val);
};

#endif