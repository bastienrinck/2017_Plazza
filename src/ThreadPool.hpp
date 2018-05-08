/*_tsync
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#pragma once

#include <netinet/in.h>
#include "datatype.hpp"
#include "Thread.hpp"

namespace Plazza {
	class ThreadPool {
	public:
		explicit ThreadPool(struct sockaddr, size_t);
		~ThreadPool();
		size_t getWorkLoad();
		void assignTask(std::string &filename, size_t type);
		void awaitThreads();
	private:
		size_t _maxThread;
		threadSync_t _tsync;
		std::vector<std::unique_ptr<Thread>> _threads;
	};
}
