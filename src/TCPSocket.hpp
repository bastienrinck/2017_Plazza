/*
** EPITECH PROJECT, 2021
** cpp_plazza
** File description:
** Created by rectoria
*/

#pragma once

namespace Plazza {
	class TCPSocket {
	public:
		TCPSocket();
		explicit TCPSocket(int fd);
		virtual ~TCPSocket() = 0;
	};
}
