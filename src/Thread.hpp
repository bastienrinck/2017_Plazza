/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#pragma once

#include <string>
#include <vector>
#include <thread>
#include <netinet/in.h>
#include "datatype.hpp"
#include "ClientSocket.hpp"

namespace Plazza {
	class Thread {
	public:
		Thread(struct sockaddr master, threadSync_t *);
		virtual ~Thread();
	private:
		void proceed();
		void proceedTask();
		void extractData(std::string &reg);
		void sendResults();

		Plazza::task_t _task;
		Plazza::ClientSocket _socket;
		Plazza::threadSync_t *_tSync;
		std::string _content;
		std::vector<std::string> _results;
		std::thread _thread;
		std::vector<std::string> _regex = {
			"(0 ?[1-9]) ?([0-9] ?){8}",
			R"(((?:(?:[^<>()\[\].,;:\s@\"]+(?:\.[^<>()\[\].,;:\s@\"]+)*)|\".+\")@(?:(?:[^<>()\[\].,;:\s@\"]+\.)+[^<>()\[\].,;:\s@\"]{2,})))",
			"([0-9]{1,3}[\\.]){3}[0-9]{1,3}"
		};
	};
}
