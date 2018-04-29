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

Plazza::Plazza::Plazza(bool _isCLI, size_t nbThread)
	: _isCLI(_isCLI),
	  _nbThread(nbThread)
{
	std::cout << "[Plazza] I have : " << _nbThread << " threads."
		<< std::endl;
}

Plazza::Plazza::~Plazza()
{
	std::cout << "[Plazza] I die\n";
}

size_t Plazza::Plazza::getNbThread() const
{
	return _nbThread;
}

void Plazza::Plazza::readCmd()
{
	while (true) {
		// TODO delete this print for final push
		std::cout << "Prompt > ";
		for (; std::getline(std::cin, cmd); ) {
			this->parseCmd(cmd);
		}
		if (std::cin.eof())
			break;
	}
}

void Plazza::Plazza::parseCmd(std::string &cmd)
{
	std::regex pattern(
		R"(([a-zA-Z _\.]{1,})(EMAIL_ADDRESS|IP_ADDRESS|PHONE_NUMBER))");
	std::cmatch cm;
	std::cout << "parseCmd in\n";
	while (std::regex_search(cmd.c_str(), cm, pattern)) {
		for (auto x:cm) {
			std::cout << x << std::endl;
		}
		//cm.str(0) contient le full match
		//cm.str(1) contient le group 1 (fichier)
		//cm.str(2) contient le group 2 (info a checher)
		cmd = cm.suffix().str();
		file = cm.str(1);
		type = cm.str(2);
		std::cout << "Fichier: " << file << "type: " << type << std::endl;
	}
	std::cout << "parseCmd out\n";
}

int Plazza::Plazza::startPlazza()
{
	this->readCmd();
	return 0;
}
