/* File: system.hpp
 * Author: Benoit Coville
 * covillebenoit@gamil.com
 * student number: c3316165
 * course COMP2240 operating systems
 * Assignment 3
 */

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>
#include <string>

#include "process.hpp"


class System
{
private:
	std::vector<Process> v_processes;
	std::vector<int> v_ready_queue;
	int m_time_quantum;
	int m_number_frame;

public:
	System(std::string fileName1, std::string fileName2, std::string fileName3="", std::string fileName4="");
	~System();



	
};

#endif
