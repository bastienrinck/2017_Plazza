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
		void createSlave();
	private:
		std::vector<Slave> mySlaves;
	};
}

#endif
