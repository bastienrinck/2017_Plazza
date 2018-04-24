/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include <iostream>
#include "plazza.hpp"

int main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
		std::cout << "IsNoGood\n";
	else
		Plazza oui(true,5);
	return 0;
}