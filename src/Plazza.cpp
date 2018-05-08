/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <unordered_map>
#include <csignal>
#include <poll.h>
#include "Plazza.hpp"

Plazza::Plazza::Plazza(bool _isCLI, size_t nbThread) : _isCLI(_isCLI),
	_nbThread(nbThread), _socket(false)
{
	auto server = dynamic_cast<ServerSocket *>(_socket.getServer());
	auto client = dynamic_cast<ClientSocket *>(_socket.getClient());

	server->setSocket(0);
	client->setSocket(server->getSocketIp(), server->getSocketPort());
	_master = client->getSockaddr();
	_socket.closeClient();
	_forkPool.setNbThreads(nbThread);
	_forkPool.setMasterSocket(_master);
	_futureObj = exitSignal.get_future();
	_output = std::thread([this] {
		retrieveData();
	});
}

Plazza::Plazza::~Plazza()
{
	exitSignal.set_value();
	_output.join();
	std::cout << "[Plazza] Quit\n";
}

void Plazza::Plazza::readCmd()
{
	// TODO delete this print for final push
	std::cout << "Prompt >";
	for (; std::getline(std::cin, _cmd);) {
		if (strcmp(_cmd.c_str(), "quit") != 0)
			parseCmd(_cmd);
		// TODO delete this print for final push
		if (!strcmp(_cmd.c_str(), "quit") || std::cin.eof())
			break;
		std::cout << "Prompt >";
	}
}

Plazza::dataTypes Plazza::Plazza::getType(std::string type) const
{
	static std::unordered_map<std::string, dataTypes> map = {
		{"EMAIL_ADDRESS", dataTypes::EMAIL},
		{"IP_ADDRESS", dataTypes::ADDR},
		{"PHONE_NUMBER", dataTypes::PHONE}};
	auto dataType = map[type];
	return dataType;
}

//cm.str(0) contient le full match
//cm.str(1) contient le group 1 (fichier)
//cm.str(2) contient le group 2 (proceedTask a checher)
void Plazza::Plazza::parseCmd(std::string &cmd)
{
	std::regex pattern(
		R"(([[:graph:]]{1,})(?: )(EMAIL_ADDRESS|IP_ADDRESS|PHONE_NUMBER))");
	std::cmatch cm;
	while (std::regex_search(cmd.c_str(), cm, pattern)) {
		_forkPool.proceedCommand(cm.str(1), getType(cm.str(2)));
		cmd = cm.suffix().str();
	}
}

int Plazza::Plazza::startPlazza()
{
	this->readCmd();
	return 0;
}

void Plazza::Plazza::retrieveData()
{
	auto server = dynamic_cast<ServerSocket *>(_socket.getServer());
	std::vector<struct pollfd> pollfd;

	pollfd.push_back({server->getSocket(), 0, 0});
	while (_futureObj.wait_for(std::chrono::milliseconds(1)) ==
		std::future_status::timeout) {
		auto res = poll(&pollfd.front(), pollfd.size(), 100);
		for (size_t i = 0; res && i < pollfd.size(); ++i) {
			if (pollfd[i].events == POLLIN &&
				pollfd[i].fd == server->getSocket()) {
				server->accept();
				pollfd.push_back(
					{server->getClient().back(), 0, 0});
				pollfd[i].events = 0;
				pollfd[i].revents = 0;
				std::cout << "New client: " << pollfd.back().fd << std::endl;
			} else if (pollfd[i].events == POLLIN) {
				std::string buf;
				server->receive(buf, static_cast<size_t>(
					std::find(server->getClient().begin(),
						server->getClient().end(),
						pollfd[i].fd) -
						server->getClient().begin()));
				std::cout << "[" << pollfd[i].fd << "] " << buf
					<< std::endl;
				pollfd[i].events = 0;
				pollfd[i].revents = 0;
			} else {
				server->closeConnection(pollfd[i].fd);
				pollfd.erase(pollfd.begin() + i);
			}
		}
	}
	exit(EXIT_SUCCESS);
}
