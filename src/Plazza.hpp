/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#pragma once

#include <ostream>
#include <glob.h>
#include <netinet/in.h>
#include <future>
#include <fstream>
#include "Socket.hpp"
#include "ForkPool.hpp"

namespace Plazza {
	class Plazza {
	public:
		Plazza(bool _isCLI, size_t nbThread);
		virtual ~Plazza();
		int startPlazza();

	private:
		void parseCmd(std::string &cmd);
		void readCmd();
		void retrieveData();
		dataTypes getType(std::string) const;

		bool acceptIncClient(std::vector<struct pollfd> &, ServerSocket *, size_t);
		bool recvClientData(std::vector<struct pollfd> &, ServerSocket *, size_t);
		bool closeClientLink(std::vector<struct pollfd> &, ServerSocket *, size_t);

		bool _isCLI;
		std::string _cmd;
		size_t _nbThread;
		Socket _socket;
		std::filebuf _fb;
		struct sockaddr _master = {0, 0};
		std::thread _output;
		ForkPool _forkPool;
		std::promise<void> exitSignal;
		std::future<void> _futureObj;

	};
}