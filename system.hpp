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
#include <list>
#include <string>
#include <unistd.h>

#include "process.hpp"


class System
{
private:
	std::vector<Process> v_processes;
	//the elements of the ready queue point on elements of the v_processes vector
	std::list<Process*> q_ready;
	//time quantum for round robin
	int m_time_quantum;
	//beginning of the last time quantum, change each time we start running another process
	//we can have this variable shared among all the processes because only one process can be executed at a time
	int m_start_quantum;
	//number total that the system can load in main memory
	int m_number_frame;
	//current time
	int m_t;
	//current process running, correspond to an index of the vector v_processes[]
	// =-1 if no process is running so it can't be a size_t
	int m_running_process;
	//time to load a frame in memory
	int m_loading_frame_time;
	//time to run a single frame
	int m_running_frame_time;
public:
	System(std::string fileName1, std::string fileName2, std::string fileName3="", std::string fileName4="");
	~System();

	//test function for see if the files have been read correctly
	void display_processes_frames()const;

	//put in the ready queue the processes who have finished to load their current frame
	void updateReadyQueue();
	void simple_RR();
	
	//return false if there is no process ready to execute
	//otherwise return true and execute the process
	bool runNextReadyProcess();
	
	void run_round_robin();
	void display_results()const;
	bool allProcessesFinshed();
};

#endif
