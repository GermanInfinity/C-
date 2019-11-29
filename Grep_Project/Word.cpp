#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Index.h"
#include "Loc_Value.h"
#include "Value.h"
#include "StringProcessing.h"

using namespace std;

//Constructor
Value::Value()
{
	location = ;//initialize vector
}

Value::Value(string key)
{
	word = key;
	

}

//Function: Adds occurrence location for each word
//Input: 
//Returns: Does not return anything
//Does: Stores the file_path, line_number and line of an element
//in an index of the location vector. 
Value::add_location()
{
	Loc_Value *new_loc = new Loc_Value();
	location.insert(location.begin(), new_loc);
	new_loc.file_path = ;
	new_loc.line_number = ;
	new_loc.line = ;
}

//Function: Prints
//Input: 
//Returns: Does not return anything
//Does: Prints out the location information of a  
Value::print_all()
{
	for (int i = 0; i < location.size(); i++)
	{
		cout << location[i].file_path << endl;
		cout << location[i].line_number << endl; 
		cout << location[i].line << endl;
	}
}