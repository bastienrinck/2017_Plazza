/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#ifndef CPP_PLAZZA_SLAVEPOOL_HPP
#define CPP_PLAZZA_SLAVEPOOL_HPP

#include "slave.hpp"

namespace Plazza {
	class slavePool {
	public:
		slavePool();
		virtual ~slavePool();
		void setNbThreads(size_t maxThreads);
		void createSlave();
		void proceedCommand(std::string &file, std::string &type);
		bool isValidFile(std::string &file);
	private:
		std::vector<Slave> mySlaves;
		size_t maxThreads;
	};
}

#endif
