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
#include "datatype.hpp"

#define TEL "(0 ?[1-9]) ?([0-9] ?){8}"
#define EM "((?:(?:[^<>()\\[\\].,;:\\s@\\\"]+(?:\\.[^<>()\\[\\].,;:\\s@\\\"]+)*)|\\\".+\\\")@(?:(?:[^<>()\\[\\].,;:\\s@\\\"]+\\.)+[^<>()\\[\\].,;:\\s@\\\"]{2,}))"
#define AD "([0-9]{1,3}[\\.]){3}[0-9]{1,3}"

namespace Plazza {
	class Threadz {
	public:
		Threadz(::Plazza::threadData_t tD);
		void Info();
		virtual ~Threadz();
		const std::vector<std::string> &get_Phone() const;
		const std::vector<std::string> &get_Email() const;
		const std::vector<std::string> &get_Adress() const;
		bool isIsWorking() const;
		std::thread memberThread() {
			return std::thread([=] { Info(); });
		}
	private:
		void getFromFile(char *reg);
		std::vector<std::string> _Phone;
		std::vector<std::string> _Email;
		std::vector<std::string> _Adress;
		threadData_t _threadData;
		std::thread _myThread;
		bool isWorking;
	};
}
#endif
