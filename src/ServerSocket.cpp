/*
** EPITECH PROJECT, 2021
** cpp_plazza
** File description:
** Created by rectoria
*/

#include <iostream>
#include <cstring>
#include <zconf.h>
#include <algorithm>
#include <arpa/inet.h>
#include "ServerSocket.hpp"
#include "Socket.hpp"

Plazza::ServerSocket::ServerSocket()
{
	_socket = socket(AF_INET, SOCK_STREAM, 6);
}

Plazza::ServerSocket::ServerSocket(int socket)
{
	_socket = socket;
}

Plazza::ServerSocket::ServerSocket(int socket, int client)
{
	struct sockaddr s_in_client{0, 0};
	socklen_t size = sizeof(_s_in);

	_socket = socket;
	_client.push_back(client);
	getsockname(socket, &_s_in, &size);
	getsockname(client, &s_in_client, &size);
	_s_in_client.push_back(s_in_client);
	_linked = true;
}

Plazza::ServerSocket::~ServerSocket()
{
	close(_socket);
	for (auto i: _client)
		close(i);
}

bool Plazza::ServerSocket::setSocket(int port)
{
	bool ret;
	auto s_in = (struct sockaddr_in *)&_s_in;
	socklen_t size = sizeof(_s_in);

	s_in->sin_family = AF_INET;
	s_in->sin_addr.s_addr = INADDR_ANY;
	s_in->sin_port = htons((unsigned short)port);
	ret = !bind(_socket, &_s_in, size);
	ret = ret && !listen(_socket, 100);
	getsockname(_socket, &_s_in, &size);
	return ret;
}

bool Plazza::ServerSocket::accept()
{
	int fd;
	struct sockaddr s_in_client = {0, 0};
	socklen_t size = sizeof(_s_in);

	fd = ::accept(_socket, &s_in_client, &size);
	if (fd != -1) {
		_client.push_back(fd);
		_s_in_client.push_back(s_in_client);
	}
	_linked = (!_linked && fd != -1) ? true : _linked;
	return _linked;
}

int Plazza::ServerSocket::send(const std::string &data, size_t pos) const
{
	ssize_t ret = 0;

	if (!_linked)
		std::cerr << "ServerSocket::send : Socket not connected."
			<< std::endl;
	else if (pos >= _client.size())
		std::cerr << "ServerSocket::send : Wrong socket pos."
			<< std::endl;
	else {
		std::string len = std::to_string(data.length());
		len = std::string(8 - len.size(), '0').append(len);
		::send(_client[pos], len.c_str(), 8, 0);
		ret = ::send(_client[pos], data.c_str(), data.size(), 0);
	}
	return static_cast<int>(ret);
}

int Plazza::ServerSocket::receive(std::string &container, size_t pos)
{
	container.clear();
	if (!_linked)
		std::cerr << "ServerSocket::recv : Socket not connected."
			<< std::endl;
	else if (pos >= _client.size())
		std::cerr << "ServerSocket::recv : Wrong socket pos."
			<< std::endl;
	else {
		char buffer[2048] = {0};
		::recv(_client[pos], buffer, 8, 0);
		auto size = std::strtoul(buffer, NULL, 10);
		for (size_t i = 0; i < size;) {
			auto len = (size - i > 2048 ? 2048 : size - i);
			memset(buffer, 0, 2048);
			i += len;
			::recv(_client[pos], buffer, len, 0);
			container += std::string(buffer);
		}
	}
	return static_cast<int>(container.length());
}

int Plazza::ServerSocket::getSocket() const
{
	return _socket;
}

std::vector<int> Plazza::ServerSocket::getClient() const
{
	return _client;
}

std::string Plazza::ServerSocket::getSocketIp() const
{
	return inet_ntoa(((struct sockaddr_in *)&_s_in)->sin_addr);
}

int Plazza::ServerSocket::getSocketPort() const
{
	return ntohs(((struct sockaddr_in *)&_s_in)->sin_port);
}

void Plazza::ServerSocket::closeConnection(int fd)
{
	auto pos = std::find(_client.begin(), _client.end(), fd);

	if (pos != _client.end())
		_client.erase(pos);
}

struct sockaddr Plazza::ServerSocket::getSockaddr() const
{
	return _s_in;
}
