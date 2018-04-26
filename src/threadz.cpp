/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include <fstream>
#include <iostream>
#include <regex>
#include "threadz.hpp"

void Plazza::Threadz::getFromFile(threadData_t thData, char *reg)
{
	auto first = thData.content.begin();
	auto last = thData.content.end();
	std::regex re(reg);
	std::match_results<decltype(first)> match;
	while (std::regex_search(first, last, match, re)) {
		switch (thData.dataType) {
			case 1:
				_Phone.push_back(match.str());
				break;
			case 2:
				_Email.push_back(match.str());
				break;
			case 3:
				_Adress.push_back(match.str());
				break;
			default:
				break;
		}
		first = std::next(match.prefix().second);
	}
}

void Plazza::Threadz::Info(threadData_t &thData)
{
	std::ifstream ifs(thData.fileName);
	if (ifs.fail()) {
		std::cerr << "Error: " << strerror(errno) << std::endl;
	}
	thData.content = std::string((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));;
	switch (thData.dataType) {
		case 1:
			getFromFile(thData, const_cast<char *>(PHONE));
			break;
		case 2:
			getFromFile(thData, const_cast<char *>(EMAIL));
			break;
		case 3:
			getFromFile(thData, const_cast<char *>(ADDR));
			break;
		default:
			break;
	}
}

Plazza::Threadz::Threadz()
{
}

Plazza::Threadz::~Threadz()
{
}

const std::vector<std::string> &Plazza::Threadz::get_Phone() const
{
	return _Phone;
}

const std::vector<std::string> &Plazza::Threadz::get_Email() const
{
	return _Email;
}

const std::vector<std::string> &Plazza::Threadz::get_Adress() const
{
	return _Adress;
}


