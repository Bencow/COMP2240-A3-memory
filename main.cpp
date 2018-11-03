/* File: main .cpp
 * Author: Benoit Coville
 * covillebenoit@gamil.com
 * student number: c3316165
 * course COMP2240 operating systems
 * Assignment 3
 */

#include <iostream>
#include <string>

#include "system.hpp"



int main(int argc, char const *argv[])
{
	if(argc < 6)
	{
		std::cout << "ERROR 1 number parameters main" << std::endl;
		exit(-1);
	}
	int frame_number = atoi(argv[1]);
	int quantum_size = atoi(argv[2]);

	// std::cout << frame_number << " " << quantum_size << std::endl;

	// System syst("S1/Process1.txt","S1/Process2.txt","S1/Process3.txt", "S1/Process4.txt");
	// System syst(frame_number, quantum_size, "S2/Process1.txt","S2/Process2.txt","S2/Process3.txt");
	
	System syst1(frame_number, quantum_size);
	if(argc == 6)
	{
		syst1.readFiles(argv[3], argv[4], argv[5]);
	}
	else if(argc == 7)
	{
		syst1.readFiles(argv[3], argv[4], argv[5], argv[6]);
	}
	else
	{
		std::cout << "ERROR 2 number parameters main" << std::endl;
		exit(-1);
	}

	syst1.run_round_robin(true);//run LRU
	std::cout<< "LRU - Fixed:" << std::endl;
	syst1.display_results();


	std::cout << std::endl 
			  << "------------------------------------------------------------"<< std::endl << std::endl
			  << "Clock - Fixed:" << std::endl;


	System syst2(frame_number, quantum_size);
	if(argc == 6)
		syst2.readFiles(argv[3], argv[4], argv[5]);
	else if(argc == 7)
		syst2.readFiles(argv[3], argv[4], argv[5], argv[6]);
	else
	{
		std::cout << "ERROR 2 number parameters main" << std::endl;
		exit(-1);
	}
	syst2.run_round_robin(false);//run LRU
	syst2.display_results();

	return 0;
}