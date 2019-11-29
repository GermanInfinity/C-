#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Island.h"
using namespace std; 

//Default constructor
Island::Island()
{
	island_name = "";
}

//Parametrized constructor
Island::Island(string name)
{
	island_name = name;
}

//Function name: insert_movie
//Inputs: A movie's name
//Returns: Does not return anything
//Does: Inserts a movie into the list of an actors movies
void Island::insert_bridge(string bridge)
{
	bridges.insert(bridge);
}

//Function name: with_bridge
//Inputs: A bridge's name
//Returns: True or false value
//Does: Checks if an island has a given bridge
bool Island::with_bridge(string bridge)
{
	int count = 0;
	while(count < bridges.get_length()) // should check this out 
	{
		if(bridges.get_value_at(count) == bridge)
			return true;
		count++;
	}
	return false;
}

//Function name: connect
//Inputs: Island object
//Returns: Name of bridge
//Does: Returns name of mutual bridge between Islands
string Island::connect(Island island2)
{
	int count = 0;
	bool k = false;
	string sim[5];
	while(count < bridges.get_length()){
		bool a; 
		//the next line iterates through the list of movies of the 
		//actor object, and compares it with the star_actors movies.
		string found_bridge = island2.bridges.find
							(bridges.get_value_at(count), a);
		
	    //cout << "In connect function: found movie: " << found_movie << endl; 
	    //cout << a << endl; 
		if (a){
			sim[count] = found_bridge;
			k = true;
			//return found_bridge;
		}
		count++;
	}
	if (k)
		return sim[0] + sim[1] + sim[2] + sim[3];
	return "";
}


//Function name: operator == 
//Inputs: Two Island objects
//Returns: True or false
//Does: Overloads the == operator to check if two Island objects are the 
//same
bool operator == (const Island &island1, const Island &island2)
{
	return (island1.island_name == island2.island_name);
}

//Function name: operator != 
//Inputs: Two Island objects
//Returns: True or false
//Does: Overloads the != operator to check if two Island objects are not the 
//same
bool operator != (const Island &island1, const Island &island2)
{
	 bool ans = (island1.island_name == island2.island_name);
	 if (ans == true)
	 	return false; 
	 return true;
}

//Function name: operator << 
//Inputs: An Island object, Ostream object
//Returns: Ostream file
//Does: Overloads the << operator to print an Islands name to an output
//file
ostream &operator << (ostream &outfile, const Island &island)
{
	outfile << island.island_name;
	return outfile;
}

//Funtion: print
//Inputs: Nothing
//Returns: Nothing
//Does: Print's the name of an Island
string Island::print()
{
	return island_name;
}