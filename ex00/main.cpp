#include "BitcoinExchange.hpp"

int main(int ac, char **av){
	if (ac == 2){
		BitcoinExchange bit;

		bit.BtcMonitoring(av[1]);
	}
	else {
		std::cerr << "Error: could not open file." << endl;
	}
}