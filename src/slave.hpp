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
#include "threadzPool.hpp"

namespace Plazza {
	class Slave {
	public:
		Slave();
		virtual ~Slave();
		int get_forkPid() const;
		void giveJob(std::string filePath, ::Plazza::dataTypes dT);
	private:
		threadPool _threadPool;
		int _forkPid;

	};
}
#endif
