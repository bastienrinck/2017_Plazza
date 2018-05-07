//
// Created by rectoria on 4/30/18.
//

#pragma once

#include <string>
#include <netinet/in.h>
#include <vector>
#include "TCPSocket.hpp"

namespace Plazza {
	class ServerSocket : public TCPSocket {
	public:
		ServerSocket();
		explicit ServerSocket(int);
		ServerSocket(int, int);
		~ServerSocket() override;

	public:
		bool setSocket(int);
		bool accept();
		int send(const std::string &, size_t = 0) const;
		int receive(std::string &, size_t = 0);
		void closeConnection(int fd);
		int getSocket() const;
		std::vector<int> getClient() const;
		std::string getSocketIp() const;
		int getSocketPort() const;
	private:
		int _socket = -1;
		std::vector<int> _client;
		struct sockaddr _s_in;
		std::vector <struct sockaddr> _s_in_client;
		bool _linked = false;
	};
}

