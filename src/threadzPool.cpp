/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include <iostream>
#include <memory>
#include "threadzPool.hpp"

void Plazza::threadPool::createThread(const ::Plazza::threadData_t &tD)
{
	_myThreads.push_back(new ::Plazza::Threadz(tD));
}

Plazza::threadPool::threadPool()
{
}

Plazza::threadPool::~threadPool()
{
}

bool Plazza::threadPool::allAsleep()
{
	auto ret = true;

	for (auto &_myThread : _myThreads) {
		if (_myThread->isIsWorking())
			ret = false;
	}
	std::cout << "InFunc(allThreadzAsleep (" << ret << ")\n";
	return ret;
}

void Plazza::threadPool::giveJob(::Plazza::threadData_t &dT)
{

	if (!_myThreads.empty()) {
		std::cout << "giveJob: Le vector n'est pas vide on regarde si il y en as un de dispo\n";
		auto worker = canWork();
		worker->Info();
	} else {
		std::cout << "giveJob: Le vector est vide on en crée un\n";
		this->createThread(dT);
		auto worker = canWork();
		worker->Info();
	}
}

::Plazza::Threadz *Plazza::threadPool::canWork()
{
	::Plazza::Threadz *worker = nullptr;

	for (auto &_myThread : _myThreads) {
		if (!_myThread->isIsWorking())
			worker = _myThread;
	}
	return worker;
}
