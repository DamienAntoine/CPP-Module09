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

// form sorted pairs
void PmergeMe::formVectorPairs(const std::vector<int>& input, std::vector<std::pair<int, int>>& pairs, int& oddElement)
{
	size_t i = 0;
	while (i < input.size() - 1)
	{
		if (input[i] <= input[i+1])
			pairs.push_back(std::make_pair(input[i], input[i+1]));
		else
			pairs.push_back(std::make_pair(input[i+1], input[i]));
		i += 2;
	}

	oddElement = -1;
	if (input.size() % 2 != 0)
		oddElement = input[input.size() - 1];
}

// extract from pairs into two groups (smaller and bigger numbers)
void PmergeMe::extractVectorElements(const std::vector<std::pair<int, int>>& pairs, std::vector<int>& mainChain, std::vector<int>& smallerElements)
{
	std::vector<std::pair<int, int> >::const_iterator it = pairs.begin();
	while (it != pairs.end())
	{
		smallerElements.push_back((*it).first);
		mainChain.push_back((*it).second);
		++it;
	}
}

// get insertion order
std::vector<size_t> PmergeMe::VectorJacobsthalSequence(size_t size)
{
	std::vector<size_t> insertionOrder;
	size_t prev = 1, curr = 1;

	while (curr < size)
	{
		insertionOrder.push_back(curr);
		size_t next = 2 * prev + curr;
		prev = curr;
		curr = next;
	}

	for (size_t i = 1; i < size; ++i) {
		if (std::find(insertionOrder.begin(), insertionOrder.end(), i) == insertionOrder.end())
			insertionOrder.push_back(i);
	}

	return insertionOrder;
}

// inset smaller numbers back
void PmergeMe::insertSmallerElements(std::vector<int>& sortedChain, const std::vector<int>& smallerElements)
{
	if (!smallerElements.empty())
		sortedChain.insert(sortedChain.begin(), smallerElements[0]);

	std::vector<size_t> insertionOrder = VectorJacobsthalSequence(smallerElements.size());

	for (size_t i = 0; i < insertionOrder.size(); ++i)
	{
		size_t idx = insertionOrder[i];
		int val = smallerElements[idx];

		std::vector<int>::iterator pos = std::lower_bound(sortedChain.begin(), sortedChain.end(), val);
		sortedChain.insert(pos, val);
	}
}

// add last element if odd number
void PmergeMe::insertOddElement(std::vector<int>& sortedChain, int oddElement)
{
	if (oddElement != -1)
	{
		std::vector<int>::iterator pos = std::lower_bound(sortedChain.begin(), sortedChain.end(), oddElement);
		sortedChain.insert(pos, oddElement);
	}
}

void PmergeMe::sortVectorHelper(std::vector<int>& vec)
{
	if (vec.size() <= 1)
		return;

	int	oddElement;
	std::vector<std::pair<int, int>>	pairs;
	formVectorPairs(vec, pairs, oddElement);

	std::vector<int> mainChain, smallerElements;
	extractVectorElements(pairs, mainChain, smallerElements);

	if (mainChain.size() > 1)
		sortVectorHelper(mainChain);

	std::vector<int> sortedChain = mainChain;

	insertSmallerElements(sortedChain, smallerElements);
	insertOddElement(sortedChain, oddElement);

	vec = sortedChain;
}

void PmergeMe::sortVector()
{
	clock_t start = clock();
	sortVectorHelper(_vecContainer);
	_vectorTimer = (double)(clock() - start) / CLOCKS_PER_SEC;
}



void PmergeMe::formListPairs(const std::list<int>& input, std::list<std::pair<int, int>>& pairs, int& oddElement)
{
	std::list<int>::const_iterator it = input.begin();

	while (std::next(it) != input.end())
	{
		int first = *it;
		int second = *std::next(it);

		if (first <= second)
			pairs.push_back(std::make_pair(first, second));
		else
			pairs.push_back(std::make_pair(second, first));

		std::advance(it, 2);
	}

	oddElement = -1;
	if (input.size() % 2 != 0) {
		std::list<int>::const_iterator last = input.begin();
		std::advance(last, input.size() - 1);
		oddElement = *last;
	}
}

void	PmergeMe::sortList()
{
	clock_t start = clock();
	sortListHelper(_listContainer);
	_listTimer = (double)(clock() - start) / CLOCKS_PER_SEC;
}

void	PmergeMe::printRes()
{

}
