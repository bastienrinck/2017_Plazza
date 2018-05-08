/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include <iostream>
#include "Plazza.hpp"

int main(int ac, char **av)
{
	int ret = 84;

	if (ac != 2)
		std::cout << "Usage: " << av[0] << ":" << std::endl
			<< "\t[Nbr_Threads]: Thread count per forks"
			<< std::endl;
	else {
		Plazza::Plazza pl(true, std::stoul(av[1]));
		pl.startPlazza();
		ret = 0;
	}
	return ret;
}