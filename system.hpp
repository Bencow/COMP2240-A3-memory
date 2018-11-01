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


class System
{
private:
	std::vector<Process> v_processes;
	std::vector<int> v_ready_queue;

public:
	System();
	~System();



	
};

#endif
