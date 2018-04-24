/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

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
