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
	System syst("Process1.txt","Process2.txt","Process3.txt");
	syst.display_processes_frames();
	syst.simple_RR();
	syst.display_results();





	return 0;
}