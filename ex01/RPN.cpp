#include "RPN.hpp"

RPN::RPN()
{}

RPN::RPN(const std::string& expr)
{
	std::istringstream iss(expr);
	std::string symbol;

	while (iss >> symbol)
		RPN::calculateExpression(symbol);

	if (stack.size() != 1)
		throw InvalidExpression();
	result = stack.top();
}

void	RPN::calculateExpression(std::string symbol)
{
	if (symbol == "+" || symbol == "-" || symbol == "*" || symbol == "/")
	{
		if (stack.size() < 2)
		{
			std::cerr << "Error: insufficient operands" << std::endl;
			return;
		}

		int b = stack.top();
		stack.pop();
		int a = stack.top();
		stack.pop();

		if (symbol == "/" && b == 0)
		{
			std::cerr << "Error: division by zero" << std::endl;
			return;
		}

		if (symbol == "+")
			stack.push(a + b);
		else if (symbol == "-")
			stack.push(a - b);
		else if (symbol == "*")
			stack.push(a * b);
		else if (symbol == "/")
			stack.push(a / b);
		}
		else if (symbol.length() == 1 && isdigit(symbol[0]))
		{
			int value = symbol[0] - '0';
			stack.push(value);
		}
		else
			std::cerr << "Error" << std::endl;
}

RPN::RPN(const RPN& other)
{
	this->stack = other.stack;
}

RPN::~RPN()
{}

RPN& RPN::operator=(const RPN& other)
{
	if(this != &other)
		this->stack = other.stack;

	return (*this);
}

const char* RPN::InvalidExpression::what() const throw()
{
	return ("Error: invalid expression format");
}
