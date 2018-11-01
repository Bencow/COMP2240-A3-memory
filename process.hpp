/* File: process.hpp
 * Author: Benoit Coville
 * covillebenoit@gamil.com
 * student number: c3316165
 * course COMP2240 operating systems
 * Assignment 3
 */


#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <vector>


class Process
{
private:
	int m_id;
	bool m_blocked;
	std::vector<int> v_frame;
	std::vector<int> v_loaded_frame;
public:
	Process();
	~Process();
	
};



#endif