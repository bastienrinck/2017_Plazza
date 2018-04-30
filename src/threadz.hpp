/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by Benjamin
*/

#ifndef CPP_PLAZZA_THREAD_HPP
#define CPP_PLAZZA_THREAD_HPP

#include <string>
#include <vector>
#include <thread>

#define TEL "(0 ?[1-9]) ?([0-9] ?){8}"
#define EM "[a-zA-Z0-9_\\\\.-]+@[a-zA-Z0-9_\\\\.-]+\\\\.[a-zA-Z0-9_\\\\.-]+"
#define AD "[0-255].[0-255].[0-255].[0-255]"

namespace Plazza {
	typedef struct threadData_s {
		size_t dataType;
		std::string fileName;
		std::string content;
	} threadData_t;

	class Threadz {
	public:
		Threadz();
		void Info(threadData_t &thData);
		virtual ~Threadz();
		const std::vector<std::string> &get_Phone() const;
		const std::vector<std::string> &get_Email() const;
		const std::vector<std::string> &get_Adress() const;
		bool isIsWorking() const;
	private:
		void getFromFile(threadData_t thData, char *reg);
		std::vector<std::string> _Phone;
		std::vector<std::string> _Email;
		std::vector<std::string> _Adress;
		threadData_t _threadData;
		bool isWorking;
	};
}
#endif
