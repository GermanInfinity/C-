/*
 * Filename: Index.h
 * Contains: Header file for Index class
 * Description: Contains all function declarations
 *
 */

#ifndef INDEX_H_
#define INDEX_H_


#include <iostream>
using namespace std; 

#include "HashNode.h"
#include "Value.h"
#include "ActualNode.h"
#include "StringProcessing.h"
#include "FileName.h"

class Index{
	public: 
		Index(); //Constructor
		~Index(); //Destructor
		void record(string); //Creates storage of index
		void insensitive_search(string, ostream &); //insenstivie search
		void sensitive_search(string, ostream &); //senstivie search
		void word_Insert(string, int); //Function to insert single words
		int get_size(); // Returns size of the hash table
		void public_test_call(string, string, int, int); //enables public 
								//access to private functions for testing. 
		int insert_HashNode_Test(); //test for node insert.


	private: 
		vector<HashNode> *table;
		int size;
		int total_elem;
		vector<FileName> aux_vector; // vector that holds filename structs

		void non_empty_insert(string, string, int, int); //Non-empty insert
		void empty_insert(string, string, int, int); // Empty insert
	
		double load_factor(double); //Calculates load factor of storage
		void load_factor_check_and_expand(int); //checks load factor 
													//and expands
		void resize(int); //Resizes appropriately
		size_t hash(string, int); // Hash function
		void expand(); //Expands and recomputes hash table
		void insert(string, HashNode*, vector<HashNode> *); //Function to
		//insert hashnodes
		ActualNode* not_found_module(int aux_v, int num_line, string word);
		//modularizing function
		
		string to_lower(string); //function to convert to lower case
};


#endif /* INDEX_H_ */