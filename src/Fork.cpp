/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include <iostream>
#include <zconf.h>
#include <chrono>
#include <sys/wait.h>
#include <unordered_map>
#include <cstring>
#include "Fork.hpp"

Plazza::Fork::Fork(struct sockaddr master, size_t maxThreads) :
	_master(master)
	, _maxThread(maxThreads)
	, _socket(true)
{
	/*auto start = std::chrono::system_clock::now();
	_forkPid = fork();
	int i = 0;
	if (!_forkPid) {
		std::cout << "Fork is born. (pid: " << getpid() << ")\n";
		while (i == 0) {
			sleep(1);
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds =
				end - start;
			if (!(_threadPool.allAsleep()))
				start = std::chrono::system_clock::now();
			if (elapsed_seconds.count() >= 4)
				i = 1;
		}
		std::cout << "Fork fork is dead\n";
		exit(0);
	}
	else
		std::cout << "So I'm the parent (pid: " << getpid()
			<< ") from chld (pid: " << _forkPid << ")\n";
			*/
	_forkPid = fork();
	if (!_forkPid) {
		_threadPool = std::unique_ptr<Plazza::ThreadPool>(
			new Plazza::ThreadPool(sockaddr(), _maxThread));
		awaitCmd();
		exit(EXIT_SUCCESS);
	}
	//_socket.closeClient();
}

Plazza::Fork::~Fork()
{
	std::cout << "[Fork] Kill fork and exiting" << std::endl;
	kill(_forkPid, SIGTERM);
}

void Plazza::Fork::proceedCmd(std::string filePath, ::Plazza::dataTypes dT)
{
	std::string temp;
	auto srv = dynamic_cast<ServerSocket *>(_socket.getServer());

	srv->send("1\n");
	srv->send(filePath + std::to_string(dT) + "\n");
}

size_t Plazza::Fork::getWorkLoad() const
{
	std::string workLoad;
	auto srv = dynamic_cast<ServerSocket *>(_socket.getServer());

	srv->send("0\n");
	srv->receive(workLoad);
	return std::stoul(workLoad);
}

void Plazza::Fork::clientCmdProceed(std::string &cmd)
{
	std::string buf;
	size_t idx;
	auto client = dynamic_cast<ClientSocket *>(_socket.getClient());

	if (!(cmd[0] - '0'))
		client->send(std::to_string(_threadPool->getWorkLoad()) + "\n");
	else {
		client->receive(buf);
		idx = static_cast<size_t>(buf.back() - '0');
		buf.pop_back();
		_threadPool->assignTask(buf, idx);
	}
}

void Plazza::Fork::awaitCmd()
{
	std::string cmd;
	auto client = dynamic_cast<ClientSocket *>(_socket.getClient());

	while (true) {
		client->receive(cmd);
		clientCmdProceed(cmd);
	}
}
