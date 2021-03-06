/* File: process.cpp
 * Author: Benoit Coville
 * covillebenoit@gamil.com
 * student number: c3316165
 * course COMP2240 operating systems
 * Assignment 3
 */
#include "process.hpp"


Process::Process(std::string fileName, int id)
{
	m_id = id;
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

	m_name = fileName;
	m_next_frame = 0;
	m_start_loading_frame = -1;
	m_loading_frame = false;
	m_blocked = false;
	m_ready = false;
	m_finish = -1;
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

void Process::load_all_frames()
{
	for(uint i = 1 ; i < 13 ; ++i)
	{
		v_loaded_frames.push_back(i);
	}
}

void Process::executeNextFrame(int t)
{
	//store this value to debug
	v_execution.push_back(v_frames[m_next_frame]);
	v_execution_time.push_back(t);
	//increment the next frame to execute
	m_next_frame++;//don't know if it will work !!!
}

bool Process::is_over()
{
	if(m_next_frame >= v_frames.size())
		return true;
	else
		return false;
}
bool Process::nextFrameLoaded()const
{
	for(uint i = 0 ; i < v_loaded_frames.size() ; ++i)
	{
		//if the next frame to load is already loaded in memory
		if(v_frames.at(m_next_frame) == v_loaded_frames[i])
		{
			return true;
		}
	}
	return false;
}

void Process::addNextFrame()
{
	v_loaded_frames.push_back(v_frames[m_next_frame]);
}

void Process::issuePageFault(int t)
{
	v_page_faults.push_back(t);
	m_start_loading_frame = t; 
	m_loading_frame = true;
}
void Process::display_page_faults()const
{
	for(uint i = 0 ; i < v_page_faults.size() ; ++i)
	{
		std::cout << v_page_faults[i] << " ";
	}
}
void Process::display_execution()const
{
	for(uint i = 0 ; i < v_execution_time.size() ; ++i)
	{
		std::cout << v_execution_time[i] << " ";
	}
	std::cout << "          ";
	for(uint i = 0 ; i < v_execution.size() ; ++i)
	{
		std::cout << v_execution[i] << " ";

	}
}
