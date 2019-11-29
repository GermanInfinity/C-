#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Actor.h"
using namespace std; 

//Default constructor
Actor::Actor()
{
	actor_name = "";
}

//Parametrized constructor
Actor::Actor(string name)
{
	actor_name = name;
}

//Function name: insert_movie
//Inputs: A movie's name
//Returns: Does not return anything
//Does: Inserts a movie into the list of an actors movies
void Actor::insert_movie(string movie)
{
	movie_list.insert(movie);
}

//Function name: in_movie
//Inputs: A movie's name
//Returns: True or false value
//Does: Checks if an actor is a given movie
bool Actor::in_movie(string movie)
{
	//NodeType<string> *temp;
	int count = 0;
	while(count < movie_list.get_length())
	{
		if(movie_list.get_value_at(count) == movie)
			return true;
		count++;
	}
	return false;
}

//Function name: connect
//Inputs: Actor object
//Returns: Name of movie
//Does: Returns name of mutual movie between actors
string Actor::connect(Actor star_actor)
{
	int count = 0;
	while(count < movie_list.get_length()){
		bool a; 
		//the next line iterates through the list of movies of the 
		//actor object, and compares it with the star_actors movies.
		string found_movie = star_actor.movie_list.find
							(movie_list.get_value_at(count), a);
		
	    //cout << "In connect function: found movie: " << found_movie << endl; 
	    //cout << a << endl; 
		if (a)
			return found_movie;
		count++;
	}
	return "";
}


//Function name: operator == 
//Inputs: Two actor objects
//Returns: True or false
//Does: Overloads the == operator to check if two actor objects are the 
//same
bool operator == (const Actor &star_actor, const Actor &famous_actor)
{
	return (star_actor.actor_name == famous_actor.actor_name);
}

//Function name: operator != 
//Inputs: Two actor objects
//Returns: True or false
//Does: Overloads the != operator to check if two actor objects are not the 
//same
bool operator != (const Actor &star_actor, const Actor &famous_actor)
{
	 bool ans = (star_actor.actor_name == famous_actor.actor_name);
	 if (ans == true)
	 	return false; 
	 return true;
}

//Function name: operator << 
//Inputs: An Actor object, Ostream object
//Returns: Ostream file
//Does: Overloads the << operator to print an actors name to an output
//file
ostream &operator << (ostream &outfile, const Actor &actor)
{
	outfile << actor.actor_name;
	return outfile;
}

//Funtion: print
//Inputs: Nothing
//Returns: Nothing
//Does: Print's the name of an actor
string Actor::print()
{
	return actor_name;
}