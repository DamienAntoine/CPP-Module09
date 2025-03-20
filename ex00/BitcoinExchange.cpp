#include "BitcoinExchange.hpp"

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
	std::ifstream file(filename);
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
				float value = std::stof(valuestr);
				_exchangeRates[date] = value;
			} catch (const std::exception& e) {}
		}
	}
}

void BitcoinExchange::processInputFile(const std::string& inputFile)
{
	std::ifstream file(inputFile);
	if (!file.is_open())
		throw(InvalidFile());

	std::string line;
	while (getline(file, line))
	{
		size_t pipe = line.find('|');
		if (pipe == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = line.substr(0, pipe);
		if (isValidDate(date) == false)
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		std::string valuestr = line.substr(pipe + 1);
		float value;
		try {
			value = stof(valuestr);
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

		float rate = getExchangeRate(date);
		float result = value * rate;

		std::cout << date << " => " << value << " = " << result << std::endl;
	}
}

float BitcoinExchange::getExchangeRate(const std::string& date) const
{
	//If the date used as input does not exist in your DB,
	//then you must use the closest date contained in your DB.
	//Be careful to use the closest previous date, not the next one.

	//Check if the exact date exists in _exchangeRates map
	//If not, find the closest previous date in the map
	//Return the exchange rate for that date
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	try {
		int year = std::stoi(date.substr(0, 4));
		int month = std::stoi(date.substr(5, 2));
		int day = std::stoi(date.substr(8, 2));

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
