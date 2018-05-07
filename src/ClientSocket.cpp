/*
** EPITECH PROJECT, 2021
** cpp_plazza
** File description:
** Created by rectoria
*/

#include <arpa/inet.h>
#include <zconf.h>
#include <iostream>
#include <cstring>
#include "ClientSocket.hpp"

Plazza::ClientSocket::ClientSocket()
{
	_socket = socket(AF_LOCAL, SOCK_STREAM, 0);
}

Plazza::ClientSocket::ClientSocket(const int fd)
{
	socklen_t size = sizeof(_s_in);

	_socket = fd;
	getsockname(fd, &_s_in, &size);
	_connected = true;
}

Plazza::ClientSocket::~ClientSocket()
{
	close(_socket);
}

bool Plazza::ClientSocket::setSocket(const std::string &ip, int port)
{
	bool ret;
	auto s_in = (struct sockaddr_in *)&_s_in;

	s_in->sin_family = AF_LOCAL;
	ret = (inet_pton(AF_LOCAL, ip.c_str(), &s_in->sin_addr.s_addr) == 1);
	s_in->sin_port = htons((unsigned short)port);
	return ret;
}

bool Plazza::ClientSocket::connect()
{
	socklen_t size = sizeof(_s_in);

	if (_socket == -1) {
		std::cerr << "ClientSocket::connect: Socket not set."
			<< std::endl;
		return (false);
	}
	_connected = !::connect(_socket, &_s_in, size);
	return _connected;
}

int Plazza::ClientSocket::send(const std::string &data) const
{
	ssize_t ret = 0;

	if (!_connected)
		std::cerr << "ClientSocket::send : Socket not connected."
			<< std::endl;
	else
		ret = ::send(_socket, data.c_str(), data.size(), 0);
	return static_cast<int>(ret);
}

int Plazza::ClientSocket::receive(std::string &container)
{
	container.clear();
	if (!_connected)
		std::cerr << "ClientSocket::recv : Socket not connected."
			<< std::endl;
	else
		for (char buffer = -1;
			::recv(_socket, &buffer, 1, 0) > 0 && buffer &&
				buffer != '\n';)
			container.push_back(buffer);
	return static_cast<int>(container.length());
}

int Plazza::ClientSocket::getSocket() const
{
	return _socket;
}

struct sockaddr Plazza::ClientSocket::getSockaddr() const
{
	return _s_in;
}
