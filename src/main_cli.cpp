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
	if (ac != 2)
		std::cout << "IsNoGood\n";
	else {
		(void)av;
		// Todo Creation du plazza
		Plazza::Plazza pl(true, std::stoul(av[1]));
		pl.startPlazza();

/*		//Todo Creation du thread pour parse le fichier
//		::Plazza::threadData_t thData;
//		thData.dT = ::Plazza::EMAIL;
//		thData.fileName = "./tests/tests.txt";
//		::Plazza::Thread th;
//		std::thread threadFoo(&Plazza::Thread::proceedTask, &th, std::ref(thData));
//		threadFoo.join();
//		usleep(5000);
//		print_vector(th.getAdress());
		//Todo fork des slave test
//		Plazza::Fork slave;
//		std::cout << "On as: " << slave.getForkPid() << std::endl;
		//Todo Donner les ordres depuis le threadpool*
		::Plazza::threadData_t thData;
		thData.dT = ::Plazza::EMAIL;
		thData.fileName = "./tests/tests.txt";
		::Plazza::ThreadPool tp;
		tp.proceedCmd(thData);
		*/
	}
	std::cout << "MAIN END\n";
	return 0;
}