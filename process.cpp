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
	m_clock_position = 0;
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
		v_last_use.push_back(0);
	}
}

void Process::executeNextFrame(int t)
{
	int index;

	//store these values to debug
	v_execution.push_back(v_frames[m_next_frame]);
	v_execution_time.push_back(t);

	
	//to know the index of the next_frame in v_loaded_frame 
	for(uint i = 0 ; i < v_loaded_frames.size() ; ++i)
	{
		if(v_frames.at(m_next_frame) == v_loaded_frames[i])
		{
			index = i;
		}
	}
	//LRU
	v_last_use.at(index) = t;

	//Clock
	v_use_bit.at(index) = true;



	//increment the next frame to execute
	m_next_frame++;
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
	v_last_use.push_back(0);
	v_use_bit.push_back(true);
}

void Process::removeFrame(bool LRU)
{
	//LRU
	if(LRU)
	{
		//find the last used frame
		int min;
		int index_min;
		for(uint i = 0 ; i < v_last_use.size() ; ++i)
		{
			if(min > v_last_use[i])
			{
				min = v_last_use[i];
				index_min = i;
			}
		}
		//remove this frame
		v_loaded_frames.erase(v_loaded_frames.begin()+index_min);
		v_last_use.erase(v_last_use.begin()+index_min);
	}
	else//CLOCK
	{
		bool found = false;
		int index;
		for(uint i = 0 ; i < v_use_bit.size()+1 ; ++i)
		{
			//if we are still inside of the vector
			if(m_clock_position + i < v_use_bit.size())
			{
				//if this bit is 0 AND we haven't found a frame to remove already
				if(v_use_bit[m_clock_position + i] == false && !found)
				{
					index = m_clock_position + i;
					found = true;
				}
				else
					v_use_bit[m_clock_position + i] = false;
			}
			else//if we exceed the size of the vector
			{
				//if this bit is 0 AND we haven't found a frame to remove already
				if(v_use_bit[(m_clock_position + i)%v_use_bit.size()] == false && !found)
				{
					index = (m_clock_position + i)%v_use_bit.size();
					found = true;
				}
				else
					v_use_bit[(m_clock_position + i)%v_use_bit.size()] = false;
			}

		}
		//remove the frame selected
		v_loaded_frames.erase(v_loaded_frames.begin()+index);
		v_last_use.erase(v_last_use.begin()+index);
	}

}

void Process::issuePageFault(int t)
{
	v_page_faults.push_back(t);
	m_start_loading_frame = t; 
	m_loading_frame = true;
}
void Process::display_page_faults()const
{
	std::cout << "{";
	for(uint i = 0 ; i < v_page_faults.size() ; ++i)
	{
		std::cout << v_page_faults[i];
		if(i != v_page_faults.size() -1)
			std::cout << ", ";//display that except the last time
	}
	std::cout << "}";
}
void Process::display_execution()const
{
	for(uint i = 0 ; i < v_execution_time.size() ; ++i)
	{
		std::cout << v_execution_time[i] << " ";
	}
	std::cout << "         ";
	for(uint i = 0 ; i < v_execution.size() ; ++i)
	{
		std::cout << v_execution[i] << " ";

	}

}
