#pragma once 

#include <iostream>

using std::cout;
using std::string;
using std::endl;

#include <stack>
#include <sstream>
class RPN{

	private:
		std::stack<int>	polish;
	public:
		RPN();
		RPN(RPN const &);
		RPN &operator=(RPN const &);
		void rpn(string const &);
		~RPN();
};