/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>

namespace Plazza {

	typedef struct task_s {
		std::string filename;
		size_t dataType;
	}task_t;

	typedef struct threadSync_s {
		std::mutex cvmtx;
		std::mutex avmtx;
		std::condition_variable cv;
		size_t available;
		std::queue<task_t> queue;
	} threadSync_t;

	enum dataTypes {
		PHONE,
		EMAIL,
		ADDR,
		EXIT
	};
}
