/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include "plazza.hpp"

Plazza::Plazza(bool _isCLI, size_t nbThread)
	: _isCLI(_isCLI),
	  _nbThread(nbThread)
{
	std::cout << "[Plazza] I have : " << _nbThread << " threads." << std::endl;
}

Plazza::~Plazza()
{
	std::cout << "[Plazza] I die\n";
}

size_t Plazza::getNbThread() const
{
	return _nbThread;
}

void Plazza::readCmd()
{
	for (std::string cmd; std::getline(std::cin, cmd); ) {
		this->parseCmd(cmd);
	}
}

void Plazza::parseCmd(std::string &cmd)
{
	std::regex pattern(R"(([a-zA-Z _\.]{1,})(EMAIL_ADDRESS|IP_ADDRESS|PHONE_NUMBER))");
	std::cmatch cm;

	while (std::regex_search(cmd.c_str(), cm , pattern)) {
		for (auto x:cm) {
			std::cout << x <<  std::endl;
		}
		//cm.str(0) contient le full match
		//cm.str(1) contient le group 1 (fichier)
		//cm.str(2) contient le group 2 (info a checher)
		cmd = cm.suffix().str();
	}
}
