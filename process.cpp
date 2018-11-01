/* File: process.cpp
 * Author: Benoit Coville
 * covillebenoit@gamil.com
 * student number: c3316165
 * course COMP2240 operating systems
 * Assignment 3
 */
#include "process.hpp"


Process::Process(std::string fileName)
{
	std::ifstream in(fileName.c_str());
	
	std::string buffer;
	int frame;

	if(!in.is_open())
		std::cout << "problem opening file: " << fileName << std::endl;

	in >> buffer;
	if(buffer != "begin")
		std::cout << fileName << " is not formatted in the right way (should start by begin)" << std::endl;

	in >> buffer;
	while(buffer != "end")
	{
		frame = std::stoi(buffer);
		v_frames.push_back(frame);
		in >> buffer;
	}

}
Process::~Process()
{}

void Process::display_frames()const
{
	for(uint i = 0 ; i < v_frames.size() ; ++i)
	{
		std::cout << v_frames[i] << " ";
	}
	std::cout << std::endl;
}
