/*
 * Filename: Value.h
 * Contains: Header file for Value class
 * Description: Contains all function declarations
 *
 */

#ifndef VALUE_H_
#define VALUE_H_

#include <iostream>
#include "Loc_Values.h"
#include "HashNode.h"
#include "ActualNode.h"
using namespace std; 

class Value{
	public: 
		Value(); //Constructor
		~Value(); //Destructor
		void add_occurences(int, int); //add occurence of value
		void get_occurences(ostream &); //prints out info of occurences
		//void insert_occurence(); //inserts occurences to the linked list
		int get_size(); //Returns size of location vectors
		int get_file_num(); //Returns file number in file array 
		int get_line_num(); //Returns line number
	private: 
		int int_file_path_loc; //index ID of file_path string
		int int_line_no; //int line number storage delcaration

		vector<Loc_Values> location; //vector of locations
		void insert_occurence(); //inserts occurences to the linked list


};
#endif /* VALUE_H_ */
