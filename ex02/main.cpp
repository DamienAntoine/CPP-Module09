#include "PmergeMe.hpp"

int main (int argc, char **argv)
{
	if (argc <= 1)
	{
		std::cerr << "Error: No inputs" << std::endl;
		return (1);
	}

	PmergeMe sorter;
	int i = 1;
	std::cout << "Before: ";
	while (i < argc)
	{
		try {
			int numbers = std::atoi(argv[i]);
			if (numbers <= 0)
			{
				std::cerr << "Error: Only positive integers allowed" << std::endl;
				return (1);
			}
			sorter.setContainers(numbers);
			std::cout << numbers << " ";
		} catch (...) {
			std::cerr << "Error: Invalid Input" << std::endl;
			return (1);
		}
		i++;
	}
	std::cout << std::endl;

	sorter.sortVector();
	sorter.sortList();

	sorter.printRes();

	return (0);
}
