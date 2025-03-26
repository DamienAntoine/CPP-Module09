#ifndef __PMERGEME_H__
#define __PMERGEME_H__

#include <vector>
#include <list>
#include <ctime>
#include <algorithm>

class PmergeMe
{
	private:
		std::vector<int> _vecContainer;
		std::list<int> _listContainer;

		double _vectorTimer;
		double _listTimer;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		~PmergeMe();

		const PmergeMe& operator=(const PmergeMe& other);

		void	sortVector();
		void	sortList();

		void	printRes();
};

#endif
