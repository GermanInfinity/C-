/*
 * Filename: StringProcessing.cpp
 * Contains: Implementation of main for StringProcessing
 * Description: Runs through an inputed string and strips it of 
 * non-alphanumeric characters
 *
 */
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include "FSTree.h"
#include "DirNode.h"
#include "StringProcessing.h"

using namespace std; 



//Function: user_input_Process
//Input: string to clean up
//Returns: cleaned up string
//Description: Cleans up an inputted string from the user
//and runs continuously
string input_process(string input)
{
	string output = "";
	bool done = false;
	while (!done)
	{
		int num_count = 0;

		for (int i = int(input.size()); i > 0; i--){
			char ghost = input[i];
			if (!isalnum(ghost))
				num_count++;
			if (isalnum(ghost))
				break;
		}

		for (int x = 0; x < int(input.size()); x++){
			char ghost = input[x];
			if (isalnum(ghost))
				output += ghost;

			if (!isalnum(ghost) and output.size() > 1 
				and x <= int(input.size()) - num_count){
				output += ghost;
			}
			
		}
		done = true;
	}
	return output;

}