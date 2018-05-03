/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include <iostream>
#include <fstream>
#include "slavePool.hpp"

Plazza::slavePool::slavePool()
{
}

Plazza::slavePool::~slavePool()
{
}

void Plazza::slavePool::createSlave()
{
}

void Plazza::slavePool::setNbThreads(size_t maxThreads)
{
	this->maxThreads = maxThreads;
}

void Plazza::slavePool::proceedCommand(std::string &file, std::string &type)
{
	std::string delim = " ";
	size_t pos = 0;
	std::string token;

	while ((pos = file.find(delim)) != std::string::npos) {
		token = file.substr(0, pos);
		file.erase(0, pos + delim.length());
		if (this->isValidFile(token))
			std::cout << "le fichier (" << token << ") est correct et " << type << std::endl;
	}
}

bool Plazza::slavePool::isValidFile(std::string &file)
{
	std::ifstream testFile(file);

	return !testFile;
}
