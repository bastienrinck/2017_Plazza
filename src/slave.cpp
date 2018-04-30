/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include <iostream>
#include <zconf.h>
#include "slave.hpp"

Plazza::Slave::Slave()
{
	int pid = fork();
	if (!pid)
		std::cout << "Slave is born. (pid: " << getpid() << ")\n";
	else
		std::cout << "So I'm the parent (pid: " << getpid()
			<< ") from chld (pid: " << pid << ")\n";
}

Plazza::Slave::~Slave()
{
	std::cout << "Slave is deadz\n";
}

