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
	while (i < argc)
	{
		if (!sorter.isValidInteger(argv[i]))
		{
			std::cerr << "Error: Only positive integers allowed" << std::endl;
			return 1;
		}
		try {
			int numbers = std::atoi(argv[i]);
			if (numbers <= 0)
			{
				std::cerr << "Error: Only positive integers allowed" << std::endl;
				return (1);
			}
			sorter.setContainers(numbers);
		} catch (...) {
			std::cerr << "Error: Invalid Input" << std::endl;
			return (1);
		}
		i++;
	}

	sorter.printBefore();

	sorter.sortVector();
	sorter.sortList();

	sorter.printRes();

	return (0);
}
