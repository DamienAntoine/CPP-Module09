#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	this->_vecContainer = other._vecContainer;
	this->_listContainer = other._listContainer;
	this->_vectorTimer = other._vectorTimer;
	this->_listTimer = other._listTimer;
}

PmergeMe::~PmergeMe()
{}

const PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		this->_vecContainer = other._vecContainer;
		this->_listContainer = other._listContainer;
		this->_vectorTimer = other._vectorTimer;
		this->_listTimer = other._listTimer;
	}
	return (*this);
}

void	PmergeMe::sortVector()
{
	clock_t start = clock();

	//first form sorted pairs
	std::vector<std::pair<int, int>> pairs;
	size_t i = 0;
	while (i < _vecContainer.size() - 1)
	{
		if (_vecContainer[i] <= _vecContainer[i+1])
			pairs.push_back(std::make_pair(_vecContainer[i], _vecContainer[i+1]));
		else
			pairs.push_back(std::make_pair(_vecContainer[i+1], _vecContainer[i]));
		i += 2;
	}

	//third extract larger number (second element for each pair) while remembering pairs
	std::vector<int> mainChain;
	std::vector<int> smallerElements;

	std::vector<std::pair<int, int> >::const_iterator it = pairs.begin();
	while (it != pairs.end())
	{
		smallerElements.push_back((*it).first);
		mainChain.push_back((*it).second);
		++it;
	}

	int oddElement = -1;
	if (_vecContainer.size() % 2 != 0) //element not paired if its an odd number of elements
		oddElement = _vecContainer[_vecContainer.size() - 1];

	//fourth sort larger numbers
	if (mainChain.size() > 1)
	{
		std::vector<int> temp = mainChain;

		mainChain.clear();

		size_t j = 0;
		while (j < temp.size())
		{
			_vecContainer.push_back(temp[j]);
			++j;
		}
		sortVector();

		mainChain = _vecContainer;//put back to mainchain
		_vecContainer.clear();
	}

	//fifth insert smallest number right before its pair
	std::vector<int> sortedChain = mainChain;
	if (!smallerElements.empty())
		sortedChain.insert(sortedChain.begin(), smallerElements[0]);

	//insert rest of numbers with binary search
	std::vector<size_t> insertionOrder;
	size_t prev = 1, curr = 1;
	while (curr < smallerElements.size())
	{
		insertionOrder.push_back(curr);
		size_t next = 2 * prev + curr;
		prev = curr;
		curr = next;
	}

	// add remaining numbers
	for (size_t i = 1; i < smallerElements.size(); ++i)
	{
		if (std::find(insertionOrder.begin(), insertionOrder.end(), i) == insertionOrder.end())
			insertionOrder.push_back(i);
	}

	// insert smaller numbers
	for (size_t i = 0; i < insertionOrder.size(); ++i)
	{
		size_t idx = insertionOrder[i];
		int val = smallerElements[idx];

		// find where to insert
		std::vector<int>::iterator pos = std::lower_bound(sortedChain.begin(), sortedChain.end(), val);
		sortedChain.insert(pos, val);
	}

	//add odd element back
	if (oddElement != -1)
	{
		std::vector<int>::iterator pos = std::lower_bound(
			sortedChain.begin(), sortedChain.end(), oddElement);
		sortedChain.insert(pos, oddElement);
	}

	_vecContainer = sortedChain;
	_vectorTimer = (double)(clock() - start) / CLOCKS_PER_SEC;
}

void	PmergeMe::sortList()
{
	clock_t start = clock();

    // Implement Ford-Johnson using list operations
    // - Random access is O(n)
    // - Binary search requires iteration
    // - Insertions are O(1) with iterator

	_listTimer = (double)(clock() - start) / CLOCKS_PER_SEC;
}

void	PmergeMe::printRes()
{

}
