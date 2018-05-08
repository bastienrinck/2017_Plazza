/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#pragma once

#include <vector>
#include "Fork.hpp"

namespace Plazza {
	class ForkPool {
	public:
		ForkPool();
		~ForkPool();
		void setNbThreads(size_t maxThreads);
		void setMasterSocket(struct sockaddr);
		void proceedCommand(std::string file, dataTypes type);
		void cleanForkList();
	private:
		void createFork();
		bool isValidFile(std::string &file) const;
		size_t getLeastLoaded();

		struct sockaddr _master = {0, 0};
		std::vector<std::unique_ptr<Plazza::Fork>> _forks;
		size_t _maxThreads = 0;
	};
}
