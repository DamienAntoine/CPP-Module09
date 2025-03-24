#include "BitcoinExchange.hpp"
#include <sstream>

BitcoinExchange::BitcoinExchange(const std::string& databaseFile)
{
	try {
		loadDatabase(databaseFile);
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _exchangeRates(other._exchangeRates)
{}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		this->_exchangeRates = other._exchangeRates;
	return (*this);
}

void BitcoinExchange::loadDatabase(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw (InvalidFile());

	std::string line;
	while (getline(file, line))
	{
		size_t comma = line.find(',');
		if (comma != std::string::npos)
		{
			std::string date = line.substr(0, comma);
			std::string valuestr = line.substr(comma + 1);
			try {
				std::istringstream iss(valuestr);
				float value;
				iss >> value;
				if (iss.fail()) {
					throw std::runtime_error("Not a valid number");
				}
				_exchangeRates[date] = value;
			} catch (const std::exception& e) {}
		}
	}
}

void BitcoinExchange::processInputFile(const std::string& inputFile)
{
	std::ifstream file(inputFile.c_str());
	if (!file.is_open())
		throw(InvalidFile());

	std::string line;
	bool firstLine = true;
	while (getline(file, line))
	{
		if (firstLine)
		{
			firstLine = false;
			if (line.find("date") != std::string::npos)
				continue;
		}

		size_t pipe = line.find('|');
		if (pipe == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = line.substr(0, pipe);

		date.erase(0, date.find_first_not_of(" \t"));
		date.erase(date.find_last_not_of(" \t") + 1);

		if (isValidDate(date) == false)
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		std::string valuestr = line.substr(pipe + 1);
		float value;
		try {
			std::istringstream iss(valuestr);
			iss >> value;
			if (iss.fail())
				throw std::runtime_error("Not a valid number");
		} catch (const std::exception& e) {
			std::cerr << "Error: bad input => " << valuestr << std::endl;
			continue;
		}

		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		try {
			float rate = getExchangeRate(date);
			float result = value * rate;
			std::cout << date << " => " << value << " = " << result << std::endl;
		} catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
			continue ;
		}
	}
}

float BitcoinExchange::getExchangeRate(const std::string& date) const
{
	std::map<std::string, float>::const_iterator iterator = _exchangeRates.find(date);

	if (iterator != _exchangeRates.end())
		return (iterator->second);

	iterator = _exchangeRates.upper_bound(date);

	if (iterator == _exchangeRates.begin())
		throw InvalidDate();

	iterator--;
	return (iterator->second);
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	try {
		std::istringstream iss_year(date.substr(0, 4));
		std::istringstream iss_month(date.substr(5, 2));
		std::istringstream iss_day(date.substr(8, 2));

		int year, month, day;
		iss_year >> year;
		iss_month >> month;
		iss_day >> day;

		if (iss_year.fail() || iss_month.fail() || iss_day.fail())
			return false;

		if (year < 2009 || year > 2025)
			return (false);
		if (month < 1 || month > 12)
			return (false);

		bool isLeapYear = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
		int maxDays;
		if (month == 2)
		{
			if (isLeapYear)
				maxDays = 29;
			else
				maxDays = 28;
		}
		else if (month == 4 || month == 6 || month == 9 || month == 11)
			maxDays = 30;
		else
			maxDays = 31;

		if (day < 1 || day > maxDays)
			return (false);

		return (true);
	} catch (...) {
		return (false);
	}
}

const char* BitcoinExchange::InvalidFile::what() const throw()
{
	return ("Error: could not open file.");
}

const char* BitcoinExchange::InvalidDate::what() const throw()
{
	return ("Error: no data available for this date.");
}
