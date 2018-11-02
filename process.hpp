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
	//sequence of frames to execute
	std::vector<int> v_frames;
	//stores the number of frame loaded in memory 
	std::vector<int> v_loaded_frames;
	std::string m_name;
	//stores the time of all the page faults issued by this process
	std::vector<int> v_page_faults;
	//stores the frames already executed by the process
	std::vector<int> v_execution;
	//stores the time when this process was running
	std::vector<int> v_execution_time;
	
	int m_id;
	//next frame to execute, index of the vector v_frames
	size_t m_next_frame;
	//time when the last page fault was issued
	int m_start_loading_frame;
	//true if the process is loading a frame at the moment
	bool m_loading_frame;
	//may be useless...
	bool m_blocked;
	//true if the process has already loaded the next frame to execute
	bool m_ready;
	//store the time when the process finished its task 
	// = -1 if the process is not finished
	int m_finish;

public:
	Process(std::string fileName, int id);
	~Process();

	//test function for see if the files have been read correctly
	void display_frames()const;
	//test function
	void load_all_frames();

	void executeNextFrame(int t);
	void tryExecuteNextFrame(int t);

	int getId()const{ return m_id; }
	
	std::string getName()const { return m_name; }

	void setFinish(int val){ m_finish = val; }
	int getFinish() const { return m_finish; }

	//accessors of m_loading_frame
	void startLoadFrame(int t);
	void stopLoadingFrame(){ m_loading_frame = false; }
	bool is_loading_frame()const { return m_loading_frame; }
	int getStartLoadFrame() const { return m_start_loading_frame; }

	//accesors of m_ready
	bool getReady() const { return m_ready; }
	void setReady(bool val){ m_ready = val; }

	void issuePageFault(int t);
	uint getNumberPageFault() const { return v_page_faults.size(); }

	//return true if the next page is already loaded = if the 
	bool nextFrameLoaded();

	//return true if the process has finished its task
	bool is_over();
	
	void display_page_faults()const;
	void display_execution()const;

};



#endif