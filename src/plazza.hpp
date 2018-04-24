/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#ifndef CPP_PLAZZA_PLAZZA_HPP
#define CPP_PLAZZA_PLAZZA_HPP

#include <iostream>
#include <glob.h>

class Plazza {
private:
	bool _isCLI;
	size_t _nbThread;
public:
	Plazza(bool _isCLI, size_t nbThread);
	virtual ~Plazza();
	size_t getNbThread() const;
};

#endif
