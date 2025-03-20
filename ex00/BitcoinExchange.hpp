#ifndef __BITCOIN_EXCHANGE_HPP__
#define __BITCOIN_EXCHANGE_HPP__

#include <map>
#include <string>
#include <iostream>
#include <fstream>

class BitcoinExchange
{
	private:
		std::map<std::string, float> _exchangeRates;

	public:
		BitcoinExchange() {}
		BitcoinExchange(const std::string& databaseFile);
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange() {}

		void loadDatabase(const std::string& filename);
		void processInputFile(const std::string& inputFile);

		float getExchangeRate(const std::string& date) const;
		bool isValidDate(const std::string& date) const;
		bool isValidValue(const float value) const;

		class InvalidFile : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

#endif
