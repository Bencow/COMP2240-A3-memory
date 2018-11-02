/* File: system.cpp
 * Author: Benoit Coville
 * covillebenoit@gamil.com
 * student number: c3316165
 * course COMP2240 operating systems
 * Assignment 3
 */
#include "system.hpp"



System::System(std::string fileName1, std::string fileName2, std::string fileName3, std::string fileName4)
{
	//Call all the constructor of all the processes passing the file name as parameter
	Process p1(fileName1);
	v_processes.push_back(p1);

	Process p2(fileName2);
	v_processes.push_back(p2);
	//if there is a 3rd file
	if(fileName3 != "")
	{
		Process p3(fileName3);
		v_processes.push_back(p3);		
	}
	//if there is a 4th file
	if(fileName4 != "")
	{
		Process p4(fileName4);
		v_processes.push_back(p4);		
	}
	//use main parameter after !
	m_time_quantum = 3;
	m_number_frame = 30;

	m_start_quantum = -1;
	m_t = 0;
	m_running_process = -1;
	m_loading_frame_time = 6;//same for all the cases
	m_running_frame_time = 1;
}

System::~System()
{}

void System::display_processes_frames()const
{
	for(uint i = 0 ; i < v_processes.size() ; ++i)
	{
		v_processes[i].display_frames();
	}
}


void System::updateReadyQueue()
{
	//got through all the processes
	for(uint i = 0 ; i < v_processes.size() ; ++i)
	{
		//if the process is currently loading a frame AND if it's not in the ready queue already
		if(v_processes[i].is_loading_frame() && !v_processes[i].getReady())
		{
			//if this process has finished to load its frame
			if(v_processes[i].getStartLoadFrame() + m_loading_frame_time <= m_t)
			{
				//add this process in the ready queue
				q_ready.push_back(i);
				v_processes[i].setReady(true);
				v_processes[i].stopLoadingFrame();
			}
		}
	}
}



bool System::allProcessesFinshed()
{
	for(uint i = 0 ; i < v_processes.size() ; ++i)
	{
		//if one process is not finished
		if(v_processes[i].getFinish() == -1 )
			return false;
	}
	return true;
}

bool System::runNextReadyProcess()
{
	//if the queue is NOT empty
	if(!q_ready.empty())
	{
		m_start_quantum = m_t;
		//run the first element of the ready queue
		m_running_process = q_ready.front();
		q_ready.pop_front();
		//run it
		v_processes[m_running_process].executeNextFrame(m_t);
		return true;
	}
	else
		return false;
}

void System::simple_RR()
{
	for(uint i = 0 ; i < v_processes.size() ; ++i)
	{
		// //load all the frames for each process
		// v_processes[i].load_all_frames();

		//put all the processes in the ready queue in the order of their index
		q_ready.push_back(i);
	}
	
	m_start_quantum = 0;
	m_running_process = q_ready.front();
	q_ready.pop_front();

	while(!allProcessesFinshed())
	{
		//if there is a process running at the moment
		//if(m_running_process != -1)
		if(true)
		{
			//if its job is over
			if(v_processes[m_running_process].is_over())
			{
				//set its exit time
				v_processes[m_running_process].setFinish(m_t);
				
				//run the next process if there is one ready
				runNextReadyProcess();
				/*
				if(!runNextReadyProcess())
				{
					//if no process available
					m_running_process = -1;//finish the program				
				}
				*/
			}
			//check if this process has expired its time quantum
			else if(m_start_quantum + m_time_quantum <= m_t)
			{
				//put this process back in the ready queue
				q_ready.push_back(m_running_process);

				runNextReadyProcess();
				/*
				//run the next process if there is one ready
				if(!runNextReadyProcess())
				{
					//if no process available
					m_running_process = -1;//finish the program		
				}*/
			}
			else//the current process can run normally
			{
				v_processes[m_running_process].executeNextFrame(m_t);
			}
		}
		m_t++;
	}
}

void System::run_round_robin()
{
	//put in the ready queue all the processes which finish loading their current frame
	updateReadyQueue();


	while(m_t <= 40)
	{
		//if there is a process running at the moment
		if(m_running_process != -1)
		{
			//check if its job is over
			if(v_processes[m_running_process].is_over())
			{
				//set its exit time
				v_processes[m_running_process].setFinish(m_t);
				//stop running this process
				m_running_process = -1;
			}
			//check if this process has expired its time quantum
			else if(m_start_quantum + m_time_quantum <= m_t)
			{
				//put this process back in the ready queue
				q_ready.push_back(m_running_process);
				m_running_process = -1;
			}
			//else check if it has the next frame to run already loaded in memory
			else if(v_processes[m_running_process].nextFrameLoaded())
			{
				//continue running this process
				v_processes[m_running_process].executeNextFrame(m_t);
				//do not issue page fault for the other processes here !
			}
			else//this process doesn't have the next frame in memory
			{
				//issue a page fault and start loading this frame
				v_processes[m_running_process].issuePageFault(m_t);
				v_processes[m_running_process].startLoadFrame(m_t);
				//stop running this process
				m_running_process = -1;
			}
		}
		//not a else because if a process issue a page fault no process is actually running
		//there is no process currently running
		if(m_running_process == -1)
		{
			if(!q_ready.empty())
			{
				//run the first element of the ready queue
				m_running_process = q_ready.front();
				m_start_quantum = m_t;
				q_ready.pop_front();
			}
			else//no process have their next frame ready
			{
				m_running_process = -1;
				//check for page fault
				for(uint i = 0 ; i < v_processes.size() ; ++i)
				{
					//if this process is not already loading a page
					if(!v_processes[i].is_loading_frame() && v_processes[i].is_over())
					{
						//issue a page fault and start loading this frame
						v_processes[i].issuePageFault(m_t);
						v_processes[m_running_process].startLoadFrame(m_t);
					}
				}
			}	
		}
		//increment time for the next loop 
		m_t++;
	}
}

void System::display_results()const
{
	//std::cout << "PID  Process Name      Turnaround Time  # Faults  Faults Times          execution trace" << std::endl;
	std::cout << "PID  Process Name      Turnaround Time  execution trace" << std::endl;
	for(uint i = 0 ; i < v_processes.size() ; ++i)
	{
		std::cout << i+1 << "    " 
				  << v_processes[i].getName() << "      "
				  << v_processes[i].getFinish() << "               ";
		//		  << v_processes[i].getNumberPageFault() << "         ";
		//v_processes[i].display_page_faults();
		v_processes[i].display_execution();
		std::cout << std::endl;
	}
}