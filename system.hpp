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
	//Only place where all the processes are stored
	std::vector<Process> v_processes;
	//the elements of the ready queue point on elements of the v_processes vector
	//ready queue stores processes which are able to run the next frame
	std::list<Process*> q_ready;
	//time quantum for round robin
	int m_time_quantum;
	//beginning of the last time quantum, change each time we start running another process
	//we can have this variable shared among all the processes because only one process can be executed at a time
	int m_start_quantum;
	//number total that the system can load in main memory
	int m_number_frame;
	//number of frame that each process can load
	int m_memory_process;

	int m_number_process;
	//true if this system have to use LRU
	bool m_LRU;

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
	System(int frame_number, int quantum_size);
	~System();

	void readFiles(std::string fileName1, std::string fileName2, std::string fileName3="", std::string fileName4="");

	//test function to see if the files have been read correctly
	void display_processes_frames()const;
	
	//Pre condition: called at the beginning of each loop
	//Post condition: put the processes who have finished to load their current frame in the ready queue 
	void updateReadyQueue();

	//Pre condition: true if the program has to use LRU algorithm, false Clock algo 
	//Post condition: main loop of the program, run the entire execution
	void run_round_robin(bool LRU);

	//Pre condition: called by run_round_robin
	//Post condition: manage the case where at t-1 the processor was running another process
	void manageNoRunningProcess();
	//Pre condition: called by run_round_robin
	//Post condition: manage the case where at t-1 the processor was idle
	void manageRunningProcess();

	//Pre condition: ready queue must not be empty
	//Post condition: run the next frame of the first element of the ready queue
	void runNextReadyProcess();

	//Pre condition: none
	//Post condition: return true if all the processes have finished their job
	bool allProcessesFinshed();

	//Pre condition: having run the simulation before
	//Post condition: display the results
	void display_results()const;
};

#endif
