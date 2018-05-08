/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#pragma once

#include <memory>
#include "TCPSocket.hpp"
#include "ServerSocket.hpp"
#include "ClientSocket.hpp"

namespace Plazza {
	class Socket {
	public:
		explicit Socket(bool);
		~Socket();

		TCPSocket *getServer() const;
		TCPSocket *getClient() const;
		void closeServer();
		void closeClient();

	private:
		std::unique_ptr<TCPSocket> _server = nullptr;
		std::unique_ptr<TCPSocket> _client = nullptr;
	};
}