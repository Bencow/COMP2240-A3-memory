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
	// System syst("S1/Process1.txt","S1/Process2.txt","S1/Process3.txt", "S1/Process4.txt");
	System syst("S2/Process1.txt","S2/Process2.txt","S2/Process3.txt");
	syst.run_round_robin(true);//run LRU
	std::cout<< "LRU - Fixed:" << std::endl;
	syst.display_results();


	std::cout << std::endl 
			  << "------------------------------------------------------------"<< std::endl << std::endl
			  << "Clock - Fixed:" << std::endl;

	System syst2("S2/Process1.txt","S2/Process2.txt","S2/Process3.txt");
	// System syst2("S1/Process1.txt","S1/Process2.txt","S1/Process3.txt", "S1/Process4.txt");
	syst2.run_round_robin(false);//run LRU
	syst2.display_results();

	return 0;
}