//
// Created by rectoria on 4/30/18.
//

#pragma once

#include <string>
#include <netinet/in.h>
#include "TCPSocket.hpp"

namespace Plazza {
	class ClientSocket : public TCPSocket {
	public:
		ClientSocket();
		explicit ClientSocket(int fd);
		~ClientSocket() override;

	public:
		bool setSocket(const std::string &, int);
		bool connect();
		int send(const std::string &) const;
		int receive(std::string &);
		int getSocket() const;
	private:
		int _socket = -1;
		struct sockaddr _s_in = {0};
		bool _connected = false;
	};
}
