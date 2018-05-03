/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include <iostream>
#include <zconf.h>
#include <chrono>
#include <sys/types.h>
#include <sys/wait.h>
#include "slave.hpp"

Plazza::Slave::Slave()
{
	auto start = std::chrono::system_clock::now();
	_forkPid = fork();
	int i = 0;
	if (!_forkPid) {
		std::cout << "Slave is born. (pid: " << getpid() << ")\n";
		while (i == 0) {
			sleep(1);
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds =
				end - start;
			if (!(_threadPool.allAsleep()))
				start = std::chrono::system_clock::now();
			if (elapsed_seconds.count() >= 4)
				i = 1;
		}
		std::cout << "Slave fork is dead\n";
		exit(0);
	}
	else
		std::cout << "So I'm the parent (pid: " << getpid()
			<< ") from chld (pid: " << _forkPid << ")\n";
}

Plazza::Slave::~Slave()
{
	waitpid(_forkPid, 0 ,0);
	std::cout << "Slave is deadz\n";
}

int Plazza::Slave::get_forkPid() const
{
	return _forkPid;
}

void Plazza::Slave::giveJob(std::string filePath, ::Plazza::dataTypes dT)
{
	(void)filePath;
	(void)dT;
}
