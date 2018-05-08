/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include <iostream>
#include <fstream>
#include "ForkPool.hpp"

Plazza::ForkPool::ForkPool() = default;

Plazza::ForkPool::~ForkPool() = default;

void Plazza::ForkPool::createFork()
{
	std::cout << "[ForkPool] Creating a slave" << std::endl;
	_slaves.push_back(
		std::unique_ptr<Plazza::Fork>(new Fork(_master, _maxThreads)));
}

void Plazza::ForkPool::setNbThreads(size_t maxThreads)
{
	_maxThreads = maxThreads;
}

void Plazza::ForkPool::proceedCommand(std::string file, dataTypes type)
{
	std::cout << "je suis la" << std::endl;
	if (isValidFile(file))
		_slaves[getLeastLoaded()]->proceedCmd(file, type);
}

bool Plazza::ForkPool::isValidFile(std::string &file) const
{
	std::ifstream testFile(file);

	return testFile.is_open();
}

void Plazza::ForkPool::setMasterSocket(struct sockaddr master)
{
	_master = master;
}

size_t Plazza::ForkPool::getLeastLoaded()
{
	size_t temp;
	size_t idx = SIZE_MAX;
	size_t minLoad = 0;

	for (size_t i = 0; i < _slaves.size(); ++i) {
		temp = _slaves[i]->getWorkLoad();
		idx = (temp && minLoad < temp) ? i : idx;
		minLoad = (temp && minLoad < temp) ? temp : minLoad;
	}
	if (!minLoad && idx == SIZE_MAX) {
		createFork();
		idx = _slaves.size() - 1;
	}
	return idx;
}
