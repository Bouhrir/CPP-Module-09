#pragma once 

#include <iostream>
#include <fstream>
#include <map>
#include <stdlib.h>
#include <limits.h>
#include <sstream>
using std::cout;
using std::string;
using std::endl;
class BitcoinExchange {
	private:
		std::map<string, string> arr;
	public:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &);
		BitcoinExchange &operator=(BitcoinExchange const &);
		void BtcMonitoring(string const &);
		~BitcoinExchange();
};