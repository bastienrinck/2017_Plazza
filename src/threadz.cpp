/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include "threadz.hpp"

void Plazza::Threadz::getFromFile(char *reg)
{
	auto first = _threadData.content.begin();
	auto last = _threadData.content.end();
	std::regex re(reg);
	std::match_results<decltype(first)> match;

	while (std::regex_search(first, last, match, re)) {
		switch (_threadData.dT) {
			case PHONE:
				_Phone.push_back(match.str());
				break;
			case EMAIL:
				_Email.push_back(match.str());
				break;
			case ADDR:
				_Adress.push_back(match.str());
				break;
			default:
				break;
		}
		std::advance(first, match.position(0) + match.length(0));
	}
}

void Plazza::Threadz::Info()
{
	isWorking = true;
	std::cout << "\tThreadz is WORKING\n";
	std::ifstream ifs(_threadData.fileName);
	if (ifs.fail()) {
		std::cerr << "Error: " << strerror(errno) << std::endl;
	}
	_threadData.content = std::string((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));;
	switch (_threadData.dT) {
		case PHONE:
			getFromFile(const_cast<char *>(TEL));
			break;
		case EMAIL:
			getFromFile(const_cast<char *>(EM));
			break;
		case ADDR:
			getFromFile(const_cast<char *>(AD));
			break;
		default:
			break;
	}
	isWorking = false;
	std::cout << "\tThreadz is NOT WORKING\n";
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

bool Plazza::Threadz::isIsWorking() const
{
	return isWorking;
}

Plazza::Threadz::Threadz(::Plazza::threadData_t tD)
	: isWorking(false)
{
	std::cout << "\tThreadz is created\n";
}

Plazza::Threadz::~Threadz()
{
	_myThread.detach();
	std::cout << "\tThreadz is destryed\n";
}
