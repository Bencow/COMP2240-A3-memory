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
	//LRU: vector same size as v_loaded_frames, store the time of the last use 
	//of the frame at the same index in v_loaded_frames
	std::vector<int> v_last_use;
	//CLOCK: 
	std::vector<bool> v_use_bit;
	size_t m_clock_position;

	//name of the process
	std::string m_name;
	//stores the time of all the page faults issued by this process
	std::vector<int> v_page_faults;
	//stores the frames already executed by the process
	std::vector<int> v_execution;
	//stores the time when this process was running
	std::vector<int> v_execution_time;
	
	int m_id;
	//next frame to execute, index of vector v_frames
	size_t m_next_frame;
	//time when the last page fault was issued
	int m_start_loading_frame;
	//true if the process is loading a frame at the moment = blocked state
	bool m_loading_frame;
	//may be useless...
	bool m_blocked;
	//true if the process has already loaded the next frame to execute
	//this boolean is set to true when the process is put in the ready queue 
	bool m_ready;
	//store the time when the process finished its task 
	// = -1 if the process is not finished
	int m_finish;

public:
	Process(std::string fileName, int id);
	~Process();

	//test function to see if the files have been read correctly
	void display_frames()const;
	
	//Pre condition: none
	//Post condition: test funtion for debugging purposes
	void load_all_frames();


	//Pre condition: none
	//Post condition: return the id of the process
	int getId()const{ return m_id; }
	//Pre condition: none
	//Post condition: return the name of the file where the process was loaded
	std::string getName()const { return m_name; }
	//Pre condition: the process has finished its task
	//Post condition: set the time when the process exit the system 
	void setFinish(int val){ m_finish = val; }
	//Pre condition: none
	//Post condition: return the value of the
	int getFinish() const { return m_finish; }

	bool getReady() const { return m_ready; }
  
	void setReady(bool val){ m_ready = val; }
	
	//only called in System::updateReadyQueue
	//accessors of m_loading_frame
	void stopLoadingFrame(){ m_loading_frame = false; }

	//Pre condition: none
	//Post condition: return true if the process is loading a frame at the moment (=blocked state)
	bool is_loading_frame()const { return m_loading_frame; }

	//Pre condition: the process must be loading a frame
	//Post condition: return the time where the process started to load the frame
	int getStartLoadFrame() const { return m_start_loading_frame; }

	//Pre condition: called if the process doesn't have the next frame to esecute in memory
	//Post condition: issue a page fault and start loading the next frame 
	void issuePageFault(int t);


	uint getNumberPageFault() const { return v_page_faults.size(); }
	
	//Pre condition: none
	//Post condition: //return true if the next page is already loaded
	bool nextFrameLoaded()const;
	
	//Pre condition: Process must be able to execute the next frame,
	//current time of the system as parameter
	//Post condition: execute the current time
	void executeNextFrame(int t);
	
	//Pre condition: called when a frame has finished to be loaded
	//Post condition: add the m_next_frame to the v_loaded_frames
	void addNextFrame();

	//Pre condition: P wants to add a frame but doesn't have any free memory
	//Param: true if LRU algo false if Clock algo
	//Post condition: remove a frame depending on the replacement algorithm choosen
	void removeFrame(bool LRU);

	//Pre condition: 
	//Post condition: 
	int getNumberFrameLoaded()const{ return v_loaded_frames.size(); }

	//Pre condition: none
	//Post condition: return true if the process has finished its task
	bool is_over();

	//Pre condition: P has to have finished its task
	//Post condition: display all the page faults
	void display_page_faults()const;

	//Pre condition: P has to have finished its task
	//Post condition: display the execution trace
	void display_execution()const;
};



#endif