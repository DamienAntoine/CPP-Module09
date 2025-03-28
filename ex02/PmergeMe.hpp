#ifndef __PMERGEME_H__
#define __PMERGEME_H__

#include <vector>
#include <list>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <iomanip>

class PmergeMe
{
	private:
		std::vector<int> _vecContainer;
		std::list<int> _listContainer;

		double _vectorTimer;
		double _listTimer;

		void	sortVectorHelper(std::vector<int>& vec);
		void	formVectorPairs(const std::vector<int>& input, std::vector<std::pair<int, int> >& pairs, int& oddElement);
		void	extractVectorElements(const std::vector<std::pair<int, int> >& pairs, std::vector<int>& mainChain, std::vector<int>& smallerElements);
		void	insertSmallerElements(std::vector<int>& sortedChain, const std::vector<int>& smallerElements);
		void	insertOddElement(std::vector<int>& sortedChain, int oddElement);
		std::vector<size_t>	VectorJacobsthalSequence(size_t size);

		void	sortListHelper(std::list<int>& list);
		void	formListPairs(const std::list<int>& input, std::list<std::pair<int, int> >& pairs, int& oddElement);
		void	extractListElements(const std::list<std::pair<int, int> >& pairs, std::list<int>& mainChain, std::list<int>& smallerElements);
		void	insertSmallerElementsList(std::list<int>& sortedChain, const std::list<int>& smallerElements);
		void	insertOddElementList(std::list<int>& sortedChain, int oddElement);
		std::list<size_t>	ListJacobsthalSequence(size_t size);


	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		~PmergeMe();

		const PmergeMe& operator=(const PmergeMe& other);

		bool	isValidInteger(const char* str);

		void	printBefore() const;
		void	setContainers(int number);
		void	sortVector();
		void	sortList();
		void	printRes();
};

#endif
