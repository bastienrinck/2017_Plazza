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
		_server = new Plazza::ServerSocket(-1, _fd[0]);
		_client = new Plazza::ClientSocket(_fd[1]);
	} else {
		_server = new Plazza::ServerSocket();
		_client = new Plazza::ClientSocket();
	}
}

Plazza::Socket::~Socket() = default;

Plazza::TCPSocket *Plazza::Socket::getServer() const
{
	return _server;
}

Plazza::TCPSocket *Plazza::Socket::getClient() const
{
	return _client;
}

void Plazza::Socket::closeServer()
{
	close(((Plazza::ServerSocket *)getServer())->getSocket());
}

void Plazza::Socket::closeClient()
{
	close(((Plazza::ClientSocket *)getClient())->getSocket());
}
