/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#ifndef CPP_PLAZZA_THREADZPOOL_HPP
#define CPP_PLAZZA_THREADZPOOL_HPP

#include "threadz.hpp"

namespace Plazza {
	class threadPool {
	public:
		threadPool();
		virtual ~threadPool();
		void createThread();
		bool allThreadzAsleep();
	private:
		std::vector<Threadz> myThreads;
	};
}
#endif
