/*
 * Filename: Island.h
 * Contains: Header file for Actor class
 * Description: Contains all function declarations
 *
 */

#ifndef ISLAND_H_
#define ISLAND_H_

#include <iostream>
#include <string>
#include "LinkedList.h"
using namespace std; 

class Island{
public: 
	//constructor 
	Island();
	//parametrized constructor
	Island(string);
	void insert_bridge(string); //Insert movie function
	bool with_bridge(string); //Checks if actor is in a movie
	string connect(Island star_actor); //Finds name of similar movies
	string print(); //Print's Actors name
	
	friend bool operator == (const Island &, const Island &);
	friend bool operator != (const Island &, const Island &);
	friend ostream &operator << (ostream &, const Island &);

	


private:
	string island_name;
	LinkedList<string> bridges;
	

};

#endif /* ISLAND_H_ */