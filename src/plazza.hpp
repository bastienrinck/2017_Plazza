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

namespace Plazza {
	enum dataTypes {
		PHONE,
		EMAIL,
		ADDR
	};

	class Plazza {
	private:
		bool _isCLI;
		size_t _nbThread;
		std::string _cmd;
		std::string _file;
		std::string _type;
		int _plazzaPID;
	public:
		Plazza(bool _isCLI, size_t nbThread);
		virtual ~Plazza();
		int startPlazza();
		size_t getNbThread() const;
		void parseCmd(std::string &cmd);
		void readCmd();
	};
}
#endif
