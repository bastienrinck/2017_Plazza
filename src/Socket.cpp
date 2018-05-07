/*
** EPITECH PROJECT, 2021
** cpp_plazza
** File description:
** Created by rectoria
*/

#include <sys/socket.h>
#include <zconf.h>
#include "Socket.hpp"

Plazza::Socket::Socket(bool spair)
{
	int _fd[2];

	if (spair) {
		::socketpair(AF_LOCAL, SOCK_STREAM, 0, _fd);
		_server = std::unique_ptr<TCPSocket>(
			new Plazza::ServerSocket(-1, _fd[0]));
		_client = std::unique_ptr<TCPSocket>(
			new Plazza::ClientSocket(_fd[1]));
	} else {
		_server = std::unique_ptr<TCPSocket>(
			new Plazza::ServerSocket());
		_client = std::unique_ptr<TCPSocket>(
			new Plazza::ClientSocket());
	}
}

Plazza::Socket::~Socket() = default;

Plazza::TCPSocket *Plazza::Socket::getServer() const
{
	return _server.get();
}

Plazza::TCPSocket *Plazza::Socket::getClient() const
{
	return _client.get();
}

void Plazza::Socket::closeServer()
{
	close(dynamic_cast<Plazza::ServerSocket *>(getServer())->getSocket());
}

void Plazza::Socket::closeClient()
{
	close(dynamic_cast<Plazza::ClientSocket *>(getClient())->getSocket());
}
