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
#include <zconf.h>
#include "Thread.hpp"

Plazza::Thread::Thread(struct sockaddr master, threadSync_t *tSync) : _socket()
{
	auto ip = inet_ntoa(((struct sockaddr_in *)&master)->sin_addr);
	auto port = ntohs(((struct sockaddr_in *)&master)->sin_port);

	_tSync = tSync;
	_socket.setSocket(ip, port);
	_socket.connect();
	_thread = std::thread([this] {
		proceed();
	});
}

Plazza::Thread::~Thread() = default;

void Plazza::Thread::extractData(std::string &reg)
{
	auto first = _content.begin();
	auto last = _content.end();
	std::regex re(reg);
	std::match_results<decltype(first)> match;

	while (std::regex_search(first, last, match, re)) {
		_result += match.str() + "\n";
		std::advance(first, match.position(0) + match.length(0));
	}
	if (!_result.empty()) {
		_result.pop_back();
		sendResults();
		_result.clear();
	}
	_content.clear();
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
			_tSync->cv.wait(lck, [this] {return !_tSync->queue.empty();});
		_tSync->avmtx.lock();
		_tSync->available -= 1;
		_tSync->avmtx.unlock();
		_task = _tSync->queue.front();
		_tSync->queue.pop();
		if (_task.dataType != Plazza::EXIT)
			proceedTask();
		_tSync->avmtx.lock();
		_tSync->available += 1;
		_tSync->avmtx.unlock();
		if (_task.dataType == Plazza::EXIT)
			break;
	}
	close(_socket.getSocket());
}

void Plazza::Thread::sendResults()
{
	_socket.send(_result);
}

void Plazza::Thread::join()
{
	_thread.join();
}
