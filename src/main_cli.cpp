/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#include <iostream>
#include <thread>
#include "plazza.hpp"
#include "threadz.hpp"

void print_vector(std::vector<std::string> vec)
{
	std::cout << "Print Vector:\n";
	for (std::vector<std::string>::const_iterator i = vec.begin();
		i != vec.end(); ++i)
		std::cout << *i << std::endl;
}

int main(int ac, char **av)
{
	if (ac != 2)
		std::cout << "IsNoGood\n";
	else {
		Plazza::Plazza pl(true, static_cast<size_t>(std::stoi(av[1])));
		pl.startPlazza();
//		Plazza::threadData_t thData;
//		thData.dataType = 1;
//		thData.fileName = "../tests/phone.txt";
//		Plazza::Threadz th;
//		std::thread threadFoo(&Plazza::Threadz::Info, &th, std::ref(thData));
//		threadFoo.join();
//		print_vector(th.get_Phone());
	}
	return 0;
}