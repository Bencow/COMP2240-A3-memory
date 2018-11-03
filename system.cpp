/* File: system.cpp
 * Author: Benoit Coville
 * covillebenoit@gamil.com
 * student number: c3316165
 * course COMP2240 operating systems
 * Assignment 3
 */
#include "system.hpp"



System::System(int frame_number, int quantum_size)
{	

	//use main parameter after !
	m_time_quantum = quantum_size;
	m_number_frame = frame_number;

	m_start_quantum = -1;
	m_t = 0;
	m_running_process = -1;
	m_loading_frame_time = 6;//same for all the cases
	m_running_frame_time = 1;

}

System::~System()
{}

void System::readFiles(std::string fileName1, std::string fileName2, std::string fileName3, std::string fileName4)
{
	int i = 0;
	//Call all the constructor of all the processes passing the file name as parameter
	Process p1(fileName1, i);
	v_processes.push_back(p1);
	i++;
	Process p2(fileName2, i);
	v_processes.push_back(p2);
	m_number_process = 2;
	//if there is a 3rd file
	if(fileName3 != "")
	{
		i++;
		Process p3(fileName3, i);
		v_processes.push_back(p3);		
		m_number_process = 3;
	}
	//if there is a 4th file
	if(fileName4 != "")
	{
		i++;
		Process p4(fileName4, i);
		v_processes.push_back(p4);		
		m_number_process = 4;
	}
	m_memory_process = m_number_frame/m_number_process;
}

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
				q_ready.push_back(&v_processes[i]);
				v_processes[i].setReady(true);
				v_processes[i].stopLoadingFrame();
				v_processes[i].addNextFrame();
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

void System::runNextReadyProcess()
{
	//run the first element of the ready queue
	m_running_process = q_ready.front()->getId();
	
	//remove this process from the ready queue
	q_ready.pop_front();
	v_processes[m_running_process].setReady(false);
	
	//run the next frame of this process
	m_start_quantum = m_t;
	v_processes[m_running_process].executeNextFrame(m_t);
}
void System::manageRunningProcess()
{
	//if its job is over
	if(v_processes[m_running_process].is_over())
	{
		//set its exit time
		v_processes[m_running_process].setFinish(m_t);
		//if there is ready processes waiting			
		if(!q_ready.empty())
			runNextReadyProcess();
		else//if no process available : stay idle
			m_running_process = -1;
	}
	//check if this process has expired its time quantum
	else if(m_start_quantum + m_time_quantum <= m_t)
	{
		//check if this process can run the next frame 
		if(v_processes[m_running_process].nextFrameLoaded())
		{
			//put this process back in the ready queue
			q_ready.push_back(&v_processes[m_running_process]);
			v_processes[m_running_process].setReady(true);
		}
		else//it can't run the next frame
		{
			//if there is enough memory to load this frame
			if(v_processes[m_running_process].getNumberFrameLoaded() >= m_memory_process)
			{
				v_processes[m_running_process].removeFrame(m_LRU);
			}
			//issue a page fault and start loading this frame
			v_processes[m_running_process].issuePageFault(m_t);
			//stop running this process
			m_running_process = -1;
		}
		//if there is ready processes waiting			
		if(!q_ready.empty())
		{
			runNextReadyProcess();
		}
		else//if no process available : stay idle
			m_running_process = -1;
	}
	//if the next frame is already loaded the current process can run normally
	else if(v_processes[m_running_process].nextFrameLoaded())
	{
		v_processes[m_running_process].executeNextFrame(m_t);
		//running process keep the same value
	}
	else//this process doesn't have the next frame in memory
	{
		//if there is enough memory to load this frame
		if(v_processes[m_running_process].getNumberFrameLoaded() >= m_memory_process)
		{
			v_processes[m_running_process].removeFrame(m_LRU);
		}
		//issue a page fault and start loading this frame
		v_processes[m_running_process].issuePageFault(m_t);
		//stop running this process
		m_running_process = -1;
	}
}
void System::manageNoRunningProcess()
{
	//run the next process if there is one ready
	//if there is ready procesxes waiting			
	if(!q_ready.empty())
		runNextReadyProcess();
	else//if no process available
	{
		//if no process available check for page fault 
		//check for page fault
		for(uint i = 0 ; i < v_processes.size() ; ++i)
		{
			//if this process is not already loading a page AND if this process is NOT finished
			if(!v_processes[i].is_loading_frame() && v_processes[i].getFinish() == -1)
			{
				//if there is enough memory to load this frame
				if(v_processes[i].getNumberFrameLoaded() >= m_memory_process)
				{
					v_processes[i].removeFrame(m_LRU);
				}
				//issue a page fault and start loading this frame
				v_processes[i].issuePageFault(m_t);
			}
		}
		//and stay idle
		m_running_process = -1;
	}
}

void System::run_round_robin(bool LRU)
{
	//if LRU is false run clock !
	m_LRU = LRU;
	while(!allProcessesFinshed())
	{
		updateReadyQueue();

		//if there is a process running at the moment
		if(m_running_process != -1)
		{
			manageRunningProcess();
		}
		if(m_running_process == -1)//there is no process running
		{
			manageNoRunningProcess();
		}
		m_t++;
	// usleep(100000);
	}
}

void System::display_results()const
{
	std::cout << "PID   Process Name      Turnaround Time     #Faults   Fault Times" << std::endl;
	//std::cout << "PID  Process Name      Turnaround Time  execution trace" << std::endl;
	for(uint i = 0 ; i < v_processes.size() ; ++i)
	{
		std::cout << i+1 << "     " 
				  << v_processes[i].getName() << "      "
				  << v_processes[i].getFinish() << "                "
				  << v_processes[i].getNumberPageFault() << "        ";
		v_processes[i].display_page_faults();
		std::cout <<"           ";
		std::cout << std::endl;
	}
}