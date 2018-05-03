/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#ifndef CPP_PLAZZA_DATATYPE_HPP
#define CPP_PLAZZA_DATATYPE_HPP

namespace Plazza {
	enum dataTypes {
		PHONE,
		EMAIL,
		ADDR
	};

	typedef struct threadData_s {
		dataTypes dT;
		std::string fileName;
		std::string content;
	} threadData_t;
}

#endif
