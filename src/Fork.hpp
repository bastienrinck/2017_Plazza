/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#pragma once

#include <vector>
#include <netinet/in.h>
#include <future>
#include "Thread.hpp"
#include "ThreadPool.hpp"
#include "Socket.hpp"

namespace Plazza {
	class Fork {
	public:
		Fork(struct sockaddr, size_t);
		virtual ~Fork();

		void proceedFork();
		size_t getWorkLoad();
		void proceedCmd(std::string filePath, ::Plazza::dataTypes dT);
		void exitThreads();
		int getPid() const;

	private:
		void awaitCmd();
		void clientCmdProceed(std::string &);
		void checkTimeout();

		int _forkPid;
		struct sockaddr _master;
		size_t _maxThread;
		Plazza::Socket _socket;
		std::unique_ptr<ThreadPool> _threadPool = nullptr;
		std::thread _thread;
		std::promise<void> exitSignal;
		std::future<void> _futureObj;
		std::mutex _locker;
	};
}
