#ifndef __RPN_H__
#define __RPN_H__

#include <stack>
#include <string>
#include <iostream>
#include <sstream>

class RPN
{
	private:
		std::stack<int> stack;
		int result;

	public:
		RPN();
		RPN(const std::string& expr);
		RPN(const RPN& other);
		~RPN();

		RPN& operator=(const RPN& other);

		void	validateExpression(std::string expr);
		void	calculateExpression(std::string symbol);

		int getResult() const {
			return result;
		}

		class InvalidExpression : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

#endif
