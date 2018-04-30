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
#include "slave.hpp"

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
		// Todo Creation du plazza
//		Plazza::Plazza pl(true, static_cast<size_t>(std::stoi(av[1])));
//		pl.startPlazza();

		//Todo Creation du thread pour parse le fichier
//		Plazza::threadData_t thData;
//		thData.dataType = 1;
//		thData.fileName = "./tests/phones.txt";
//		Plazza::Threadz th;
//		std::thread threadFoo(&Plazza::Threadz::Info, &th, std::ref(thData));
//		threadFoo.join();
//		print_vector(th.get_Phone());
		//Todo fork des slave test
		Plazza::Slave slave;
	}
	std::cout << "MAIN END\n";
	return 0;
}