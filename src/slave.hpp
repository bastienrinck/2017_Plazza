/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#ifndef CPP_PLAZZA_SLAVE_HPP
#define CPP_PLAZZA_SLAVE_HPP

#include <vector>
#include "threadz.hpp"

namespace Plazza {
	class Slave {
	public:
		Slave();
		virtual ~Slave();
	private:
		std::vector<Plazza::Threadz> myThreads;

	};
}
#endif
