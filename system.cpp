/* File: system.cpp
 * Author: Benoit Coville
 * covillebenoit@gamil.com
 * student number: c3316165
 * course COMP2240 operating systems
 * Assignment 3
 */
#include <system.hpp>



System::System(std::string fileName1, std::string fileName2, std::string fileName3, std::string fileName4):
//use main parameter after !
m_time_quantum(3),
m_number_max_frame(30)
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

}