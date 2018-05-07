/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#ifndef CPP_PLAZZA_SLAVEPOOL_HPP
#define CPP_PLAZZA_SLAVEPOOL_HPP

#include <vector>
#include "Fork.hpp"

namespace Plazza {
	class ForkPool {
	public:
		ForkPool();
		virtual ~ForkPool();
		void setNbThreads(size_t maxThreads);
		void setMasterSocket(struct sockaddr);
		void proceedCommand(std::string file, dataTypes type);
	private:
		void createFork();
		bool isValidFile(std::string &file) const;
		size_t getLeastLoaded();

		struct sockaddr _master = {0, 0};
		std::vector<std::unique_ptr<Plazza::Fork>> _slaves;
		size_t _maxThreads = 0;
	};
}

#endif
