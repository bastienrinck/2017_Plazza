/*
** EPITECH PROJECT, 2021
** cpp_plazza
** File description:
** Created by rectoria
*/

#include <iostream>
#include <cstring>
#include <zconf.h>
#include <arpa/inet.h>
#include "ServerSocket.hpp"

Plazza::ServerSocket::ServerSocket()
{
	_socket = socket(AF_LOCAL, SOCK_STREAM, 0);
}

Plazza::ServerSocket::ServerSocket(int socket)
{
	_socket = socket;
}

Plazza::ServerSocket::ServerSocket(int socket, int client)
{
	struct sockaddr s_in_client;
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

	s_in->sin_family = AF_LOCAL;
	s_in->sin_addr.s_addr = INADDR_ANY;
	s_in->sin_port = htons((unsigned short)port);
	ret = !bind(_socket, &_s_in, size);
	ret = ret && !listen(_socket, 42);
	return ret;
}

bool Plazza::ServerSocket::accept()
{
	int fd;
	struct sockaddr s_in_client = {0};
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
		std::cerr << "ServerSocket::send : Wrong socket pos." << std::endl;
	else
		ret = ::send(_client[pos], data.c_str(), data.size(), 0);
	return static_cast<int>(ret);
}

int Plazza::ServerSocket::receive(std::string &container, size_t pos)
{
	container.clear();
	if (!_linked)
		std::cerr << "ServerSocket::recv : Socket not connected."
			<< std::endl;
	else if (pos >= _client.size())
		std::cerr << "ServerSocket::recv : Wrong socket pos." << std::endl;
	else
		for (char buffer = -1;
			::recv(_client[pos], &buffer, 1, 0) > 0 && buffer &&
				buffer != '\n';)
			container.push_back(buffer);
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
	return  ntohs(((struct sockaddr_in *)&_s_in)->sin_port);
}
