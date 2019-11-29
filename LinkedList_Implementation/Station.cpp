/* 
 * Station.cpp
 * COMP15
 * Fall 2018
 *
 * Implementation of the Station class for homework 2
 */

#include "Station.h"

// Constructor
Station::Station()
{
	name = "NoName";
    access = false;
}

// Parameterized Constructor
Station::Station(string input_name, bool input_access)
{
    name = input_name;
    access = input_access;
}

// Function:is_equal
// Input: a Station object
// Returns: True or False
// Does: Checks if a Station object has the same info as the Station 
// passed as a parameter. 
bool Station::is_equal(Station s)
{
    if (name == s.getName() and access == s.getAccess())
    {
    	return true;
    }
    return false;
}

// Function: print
// Input: ostream object
// Returns: Doesn't return anything but prints out to a file. 
// Does: It prints out the name of the station and it's availability.
void Station::print(ostream &outfile)
{
	if (access)
	{
		outfile << name << " A";
	}
	else 
	{
		outfile << name << " U";
	}
    
}



