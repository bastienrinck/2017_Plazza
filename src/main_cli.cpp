/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include <iostream>
#include <thread>
#include <zconf.h>
#include "Plazza.hpp"

void print_vector(std::vector<std::string> vec)
{
	std::cout << "Print Vector:\n";
	for (std::vector<std::string>::const_iterator i = vec.begin();
		i != vec.end(); ++i)
		std::cout << *i << std::endl;
}

int main(int ac, char **av)
{
	int ret = 0;
	if (ac != 2) {
		ret = 84;
		std::cout << "Usage: ./Plazza NUMBERS_THREADS\n";
	}
	else {
		// Todo Creation du plazza
		Plazza::Plazza pl(true, std::stoul(av[1]));
		pl.startPlazza();
	}
	return 0;
}