/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include "threadzPool.hpp"

void Plazza::threadPool::createThread()
{
	Plazza::Threadz th;
	myThreads.push_back(th);
}

Plazza::threadPool::threadPool()
{
}

Plazza::threadPool::~threadPool()
{
}

bool Plazza::threadPool::allThreadzAsleep()
{
	return true;
}
