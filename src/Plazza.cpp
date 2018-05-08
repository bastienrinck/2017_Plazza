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

	_fb.open ("plazza.log", std::ios::out);
	server->setSocket(0);
	client->setSocket(server->getSocketIp(), server->getSocketPort());
	_master = server->getSockaddr();
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
	_fb.close();
}

void Plazza::Plazza::readCmd()
{
	for (; std::getline(std::cin, _cmd);) {
		int cmp = strcmp(_cmd.c_str(), "quit");
		if (cmp)
			parseCmd(_cmd);
		if (!cmp || std::cin.eof())
			break;
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

bool Plazza::Plazza::acceptIncClient(std::vector<struct pollfd> &pollfd,
	ServerSocket *server, size_t idx
)
{
	bool ret = false;
	if (pollfd[idx].revents & POLLIN &&
		pollfd[idx].fd == server->getSocket()) {
		server->accept();
		pollfd[idx].revents = 0;
		pollfd.push_back({server->getClient().back(), POLLIN, 0});
		ret = true;
	}
	return ret;
}

bool Plazza::Plazza::recvClientData(std::vector<struct pollfd> &pollfd,
	ServerSocket *server, size_t idx
)
{
	bool ret = false;
	std::ostream stream(&_fb);

	if (pollfd[idx].revents & POLLIN) {
		std::string buf;
		if (server->receive(buf, idx - 1)) {
			std::cout << buf << std::endl;
			stream << buf << std::endl;
			pollfd[idx].revents = 0;
			ret = true;
		}
	}
	return ret;
}

bool Plazza::Plazza::closeClientLink(std::vector<struct pollfd> &pollfd,
	ServerSocket *server, size_t idx
)
{
	bool ret = false;
	
	if (pollfd[idx].revents & POLLIN) {
		server->closeConnection(pollfd[idx].fd);
		pollfd.erase(pollfd.begin() + idx);
		ret = true;
	}
	return ret;
}

void Plazza::Plazza::retrieveData()
{
	auto server = dynamic_cast<ServerSocket *>(_socket.getServer());
	std::vector<struct pollfd> pollfd;

	pollfd.push_back({server->getSocket(), POLLIN, 0});
	while (_futureObj.wait_for(std::chrono::milliseconds(1)) ==
		std::future_status::timeout) {
		auto res = 0;
		while ((res = poll(&pollfd.front(), pollfd.size(), 1)) > 0)
			for (size_t i = 0; res && i < pollfd.size(); ++i) {
				if (acceptIncClient(pollfd, server, i) ||
					recvClientData(pollfd, server, i) ||
					closeClientLink(pollfd, server, i))
					res -= 1;
			}
	}
}