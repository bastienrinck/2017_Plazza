/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#pragma once

#include <vector>
#include <netinet/in.h>
#include "Thread.hpp"
#include "ThreadPool.hpp"
#include "Socket.hpp"

namespace Plazza {
	class Fork {
	public:
		Fork(struct sockaddr, size_t);
		virtual ~Fork();
		size_t getWorkLoad() const;
		void proceedCmd(std::string filePath, ::Plazza::dataTypes dT);
		void awaitCmd();
		void clientCmdProceed(std::string &);
	private:
		int _forkPid;
		struct sockaddr _master;
		size_t _maxThread;
		Plazza::Socket _socket;
		std::unique_ptr<ThreadPool> _threadPool = nullptr;

	};
}
