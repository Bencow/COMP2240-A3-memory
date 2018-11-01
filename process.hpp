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

	std::vector<int> v_frames;
	std::vector<int> v_loaded_frames;
	
	//next frame to execute, index of the vector v_frames
	size_t m_next_frame;
	//time when the last page fault was issued
	int m_start_loading_frame;
	//true if the process is loading a frame at the moment
	bool m_loading_frame;
	//may be useless...
	bool m_blocked;
	//time when the last time
	int start_executing;
	bool m_ready;


public:
	Process(std::string fileName);
	~Process();

	//test function for see if the files have been read correctly
	void display_frames()const;

	//test function
	void load_all_frames();

	void startLoadFrame(int t);
	void stopLoadingFrame(){ m_loading_frame = false; }
	bool is_loading_frame()const { return m_loading_frame; }
	
	int getStartLoadFrame() const { return m_start_loading_frame; }



	bool getReady() const { return m_ready; }
	void setReady(bool val){ m_ready = val; }

	bool is_over();
	bool nextFrameLoaded();
	
};



#endif