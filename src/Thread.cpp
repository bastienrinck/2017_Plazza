/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include <fstream>
#include <iostream>
#include <regex>
#include <arpa/inet.h>
#include "Thread.hpp"

Plazza::Thread::Thread(struct sockaddr master, threadSync_t *tSync)
{
	auto ip = inet_ntoa(((struct sockaddr_in *)&master)->sin_addr);
	auto port = ntohs(((struct sockaddr_in *)&master)->sin_port);

	_tSync = tSync;
	_socket.setSocket(ip, port);
	_socket.connect();
	_thread = std::thread([this] {proceed();});
}

Plazza::Thread::~Thread()
{
	_thread.detach();
}

void Plazza::Thread::extractData(std::string &reg)
{
	auto first = _content.begin();
	auto last = _content.end();
	std::regex re(reg);
	std::match_results<decltype(first)> match;

	while (std::regex_search(first, last, match, re)) {
		_results.push_back(match.str());
		std::advance(first, match.position(0) + match.length(0));
	}
	sendResults();
	_content.clear();
	_results.clear();
}

void Plazza::Thread::proceedTask()
{
	std::ifstream ifs(_task.filename);

	_content = std::string((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	extractData(_regex[_task.dataType]);
}

void Plazza::Thread::proceed()
{
	while (true) {
		std::unique_lock<std::mutex> lck(_tSync->cvmtx);
		while (_tSync->queue.empty())
			_tSync->cv.wait(lck);
		_tSync->avmtx.lock();
		_tSync->available -= 1;
		_tSync->avmtx.unlock();
		_task = _tSync->queue.front();
		_tSync->queue.pop();
		proceedTask();
		_tSync->avmtx.lock();
		_tSync->available += 1;
		_tSync->avmtx.unlock();
	}

}

void Plazza::Thread::sendResults()
{
	_tSync->avmtx.lock();
	for (auto &i : _results) {
		std::cout << i << std::endl;
		_socket.send(i);
	}
	_tSync->avmtx.unlock();
}
