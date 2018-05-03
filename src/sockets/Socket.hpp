//
// Created by rectoria on 4/30/18.
//

#pragma once

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
		TCPSocket *_server;
		TCPSocket *_client;
	};
}