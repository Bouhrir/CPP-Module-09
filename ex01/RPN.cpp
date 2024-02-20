/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 21:41:39 by obouhrir          #+#    #+#             */
/*   Updated: 2024/01/26 10:52:42 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(){
	
}
bool opera(string &c){
	if (c == "*" || c == "+"
		|| c == "-" || c == "/")
		return true;
	return false;
}
int fx(int y, int x, string &fill){
	if (!fill.compare("+"))
		return x + y;
	if (!fill.compare("-"))
		return x - y;
	if (!fill.compare("*"))
		return x * y;
	if (!fill.compare("/")){
		if (y == 0)
			throw std::invalid_argument("Error: can't divison by 0");
		return x / y;
	}
	return 0;
}
void RPN::rpn(string const &av){
	if (!av.length())
		throw std::invalid_argument("Error");
	std::stringstream a(av);
	string fill;

	while (a >> fill){
		if (fill.length() != 1)
			throw std::invalid_argument("Error");
		if (!std::isdigit(fill[0]) && !opera(fill))
			throw std::invalid_argument("Error");
		if (std::isdigit(fill[0])){
			polish.push(std::atoi(fill.c_str()));
		}
		else if (opera(fill)){
			// if (polish.size() < 2)
			// 	throw std::out_of_range("Error");
			int x = polish.top();
			polish.pop();
			int y =  polish.top();
			polish.pop();
			
			int result = fx(x, y, fill);
			polish.push(result);
		}
	}
	if (polish.size() > 1)
		throw std::out_of_range("Error");
	cout<< polish.top() << endl;
}

RPN::RPN(RPN const &c){
	*this = c;
}
RPN &RPN::operator=(RPN const __unused &c){
	return *this;
}
RPN::~RPN(){
	
}