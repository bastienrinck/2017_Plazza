/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include "GuiManager.hpp"

int main(int ac, char **av)
{
	int ret = 0;
	if (ac != 2) {
		ret = 84;
		std::cout << "Usage: ./Plazza NUMBERS_THREADS\n";
	}
	else {
		std::string arg(av[1]);
		Plazza::GuiManager gui(arg);
		gui.guiLoop();
	}
	(void)(av);
	return ret;
}