#include "BitcoinExchange.hpp"

string strtrim(string const &str){
	size_t first = str.find_first_not_of(' ');
	if (first == std::string::npos)
		return str;
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, last - first + 1);
}

BitcoinExchange::BitcoinExchange(){
	std::ifstream data("data.csv");
	if (!data.is_open()){
		 std::cerr << "can't open data.csv" << endl;
		 return ;
	}
	string line;
	std::getline(data, line);
	while(std::getline(data, line)){
		size_t delimeter = line.find(",");
		if (delimeter == std::string::npos){
			std::cerr << "error: data base file" << endl;
			return;
		}
		string key = strtrim(line.substr(0, delimeter));
		string value = strtrim(line.substr(delimeter + 1, line.length()));

		arr[key] = value;
	}
	data.close();
}

void checkYMD(string &str){
	for(int i = 0;i < (int)str.length();i++){
		if (std::isdigit(str[i]))
			i++;
		else
			throw std::invalid_argument("Error: bad input => " + str);
	}
}
void check_input(string &date, string &value){
	// check validat value
	int i = 0;
	if (value[i] == '+' || value[i] == '-')
		i++; 
	for(;i < (int)value.length();i++){
		if (std::isdigit(value[i]) || value[i] == '.')
			i++;
		else
			throw std::invalid_argument("Error: not a number");
	}
	double n_value = std::strtod(value.c_str(), NULL);
	if (n_value < 0)
		throw std::invalid_argument("Error: not a positive number");
	else if ( n_value > INT_MAX)
		throw std::invalid_argument("Error: too large a number");
	
	//check validate date
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		throw std::invalid_argument("Erroe: bad input => " + date);

	string y = date.substr(0, 4); checkYMD(y);
	string m = date.substr(5, 2); checkYMD(m);
	string d = date.substr(8, 2); checkYMD(d);
	

	double n_y = std::strtod(y.c_str(), NULL);
	double n_m = std::strtod(m.c_str(), NULL);
	double n_d = std::strtod(d.c_str(), NULL);

	if (n_y < 2009 || n_y > 2022
		|| n_m < 1 || n_m > 12 
		|| n_d < 1 || n_d > 31)
		throw std::invalid_argument("Erroe: not found => " + date);
}

string preDATE(string &date){
	int year = std::atoi(date.substr(0, 4).c_str());
	int mounth = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	int mounthDAYS[12] = {31,28,31,30,31,30,31,30,31,30,31,30};
	day--;
	if (day == 0){
		mounth--;
		if (mounth == 0){
			mounth = 12;
			year--;
		}
		day = mounthDAYS[mounth];
	}

	return date;
}
void BitcoinExchange::BtcMonitoring(string const &input){
	std::ifstream in(input.c_str());
	if (!in.is_open()){
		std::cerr << "can't open input file" << endl;
		return ;
	}
	string line;
	std::getline(in, line);
	if (!line.compare("date | value")){
		std::cerr << "Error : invalid file format" << endl;
		return ;
	}
	while (std::getline(in, line)){
		size_t pip = line.find("|");
		if (pip == std::string::npos){
			std::cerr << "Error: bad input => " << line << endl; 
			continue;
		}
		string date = strtrim(line.substr(0, pip));
		string value = strtrim(line.substr(pip + 1));
		try{
			check_input(date, value);
		}
		catch (std::exception &e){
			std::cerr << e.what() << endl;
		}
		string pre_date = date;
		std::map<string, string>::iterator it = arr.find(date);
		for (;it != arr.end();){
			if (it->first == date)
				break;
			it = arr.find(date);
		}
		cout << pre_date << " => " << value << " = " << std::strtod(value.c_str(), NULL) * std::strtod(it->second.c_str(), NULL) << endl;

	}

}


BitcoinExchange::BitcoinExchange(BitcoinExchange const  &c){
	(void)c;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const  &a){

	 (void)a;
	return *this;
}
BitcoinExchange::~BitcoinExchange(){

}