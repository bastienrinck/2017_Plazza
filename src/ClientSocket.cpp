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
#include <cstdlib>
#include "ClientSocket.hpp"
#include "Socket.hpp"

Plazza::ClientSocket::ClientSocket()
{
	_socket = socket(AF_INET, SOCK_STREAM, 6);
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

	s_in->sin_family = AF_INET;
	ret = (inet_pton(AF_INET, ip.c_str(), &s_in->sin_addr.s_addr) == 1);
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
	else {
		std::string len = std::to_string(data.length());
		len = std::string(8 - len.size(), '0').append(len);
		::send(_socket, len.c_str(), 8, 0);
		ret = ::send(_socket, data.c_str(), data.size(), 0);
	}
	return static_cast<int>(ret);
}

int Plazza::ClientSocket::receive(std::string &container)
{
	char buffer[2048] = {0};

	container.clear();
	if (!_connected)
		std::cerr << "ClientSocket::recv : Socket not connected."
			<< std::endl;
	else {
		::recv(_socket, buffer, 8, 0);
		auto size = std::strtoul(buffer, NULL, 10);
		for (size_t i = 0; i < size;) {
			auto len = (size - i > 2048 ? 2048 : size - i);
			memset(buffer, 0, 2048);
			i += len;
			::recv(_socket, buffer, len, 0);
			container += std::string(buffer);
			memset(buffer, 0, len);
		}
	}
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
