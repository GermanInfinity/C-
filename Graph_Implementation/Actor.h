/*
 * Filename: Actor.h
 * Contains: Header file for Actor class
 * Description: Contains all function declarations
 *
 */

#ifndef ACTOR_H_
#define ACTOR_H_

#include <iostream>
#include <string>
#include "LinkedList.h"
using namespace std; 

class Actor{
public: 
	//constructor 
	Actor();
	//parametrized constructor
	Actor(string);
	void insert_movie(string); //Insert movie function
	bool in_movie(string); //Checks if actor is in a movie
	string connect(Actor star_actor); //Finds name of similar movies
	string print(); //Print's Actors name
	
	friend bool operator == (const Actor &, const Actor &);
	friend bool operator != (const Actor &, const Actor &);
	friend ostream &operator << (ostream &, const Actor &);

	


private:
	string actor_name;
	LinkedList<string> movie_list;
	

};

#endif /* ACTOR_H_ */