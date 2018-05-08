/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include <iostream>
#include <memory>
#include "ThreadPool.hpp"

Plazza::ThreadPool::ThreadPool(struct sockaddr master, size_t maxThread)
	: _maxThread(maxThread)
{
	_tsync.available = maxThread;
	for (size_t i = 0; i < _maxThread; ++i)
		_threads.push_back(std::unique_ptr<Plazza::Thread>(
			new Plazza::Thread(master, &_tsync)));
}

Plazza::ThreadPool::~ThreadPool() = default;

size_t Plazza::ThreadPool::getWorkLoad()
{
	size_t available;

	_tsync.avmtx.lock();
	available = _tsync.available;
	_tsync.avmtx.unlock();
	return available;
}

void Plazza::ThreadPool::assignTask(std::string &filename, size_t type)
{
	task_t task = {filename, type};

	std::unique_lock<std::mutex> lck(_tsync.cvmtx);
	_tsync.queue.push(task);
	_tsync.cv.notify_one();
}

void Plazza::ThreadPool::awaitThreads()
{
	task_t task = {"", Plazza::EXIT};

	for (size_t i = 0; i < _threads.size(); ++i) {
		std::unique_lock<std::mutex> lck(_tsync.cvmtx);
		_tsync.queue.push(task);
		lck.unlock();
		_tsync.cv.notify_one();
	}
	for (auto &i : _threads)
		i->join();
	_threads.clear();
}
