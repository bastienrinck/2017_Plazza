/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include <iostream>
#include <fstream>
#include <arpa/inet.h>
#include <signal.h>
#include <wait.h>
#include "ForkPool.hpp"

Plazza::ForkPool::ForkPool() = default;

Plazza::ForkPool::~ForkPool()
{
	for (auto &i : _forks)
		i->exitThreads();
}

void Plazza::ForkPool::createFork()
{
	_forks.push_back(
		std::unique_ptr<Plazza::Fork>(new Fork(_master, _maxThreads)));
	_forks.back()->proceedFork();
}

void Plazza::ForkPool::setNbThreads(size_t maxThreads)
{
	_maxThreads = maxThreads;
}

void Plazza::ForkPool::proceedCommand(std::string file, dataTypes type)
{
	if (isValidFile(file))
		_forks[getLeastLoaded()]->proceedCmd(file, type);
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

void Plazza::ForkPool::cleanForkList()
{
	for (size_t i = 0; i < _forks.size(); ++i)
		if (kill(_forks[i]->getPid(), 0) == -1) {
			waitpid(_forks[i]->getPid(), nullptr, WNOHANG);
			_forks.erase(_forks.begin() + i);
			i = 0;
		}
}

size_t Plazza::ForkPool::getLeastLoaded()
{
	size_t temp;
	size_t idx = SIZE_MAX;
	size_t minLoad = 0;

	cleanForkList();
	for (size_t i = 0; i < _forks.size(); ++i) {
		temp = _forks[i]->getWorkLoad();
		idx = (temp && minLoad < temp) ? i : idx;
		minLoad = (temp && minLoad < temp) ? temp : minLoad;
	}
	if (!minLoad && idx == SIZE_MAX) {
		createFork();
		idx = _forks.size() - 1;
	}
	return idx;
}
