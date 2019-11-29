#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Index.h"
#include "Value.h"
#include "HashNode.h"
#include "ActualNode.h"
#include "StringProcessing.h"

using namespace std;

//Constructor
Value::Value()
{
	int_file_path_loc = 0; 
	int_line_no = 0;
} 

Value::~Value()
{
	
} 


//Function: add_occurences
//Inputs: string, int, string
//Returns: nothing
//Does: this function takes in the file path of word, the line number
// and the line the word comes from. 
void Value::add_occurences(int file_num, int line_num)
{
	int_file_path_loc = file_num; 
	int_line_no = line_num; 
	insert_occurence();
}

//Function: insert_occurence
//Inputs: string, int, string
//Returns: nothing
//Does: this function stores the location of each 
//occurence in a linked list
void Value::insert_occurence()
{
	Loc_Values *node = new Loc_Values();
	node->file_number = int_file_path_loc;
	node->line_number = int_line_no;
	location.push_back(*node);
}

//Function: get_occurences
//Inputs: nothing
//Returns: nothing
//Does: get's the information(line number, line, file path) of each
//occurence in the linked list
// void Value::get_occurences(ostream &out)
// {
// 	for (int i = 0; i < int(location.size()); i++){
// 		out << location[i].file_path << ":" << location[i].line_number << ":" 
// 		<< location[i].line << endl;
// 	}
// }

//Function: get_file_num
//Inputs: nothing
//Returns: nothing
//Does: returns the position of a file in the file array
int Value::get_file_num()
{
	return int_file_path_loc;
}

//Function: get_line_num
//Inputs: nothing
//Returns: nothing
//Does: returns a line number in the file array 
int Value::get_line_num()
{
	return int_line_no;
}

