/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#ifndef CPP_PLAZZA_THREADZPOOL_HPP
#define CPP_PLAZZA_THREADZPOOL_HPP

#include "datatype.hpp"
#include "threadz.hpp"

namespace Plazza {
	class threadPool {
	public:
		threadPool();
		virtual ~threadPool();
		void createThread(const ::Plazza::threadData_t &tD);
		void giveJob(threadData_t &dT);
		bool allAsleep();
		::Plazza::Threadz *canWork();
	private:
		std::vector<Threadz *> _myThreads;
	};
}
#endif
