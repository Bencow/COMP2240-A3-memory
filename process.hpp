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
#include <string>
#include <iostream>
#include <fstream>

class Process
{
private:
	int m_id;
	bool m_blocked;
	std::vector<int> v_frames;
	std::vector<int> v_loaded_frames;
public:
	Process(std::string fileName);
	~Process();

	void display_frames()const;
	
};



#endif