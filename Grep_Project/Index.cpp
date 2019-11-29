/* Akwarandu Ugo Nwachuku 
* Filename: FSTreeTraversal_test.cpp
* Description: This is the index class, essentially the hash table class
* It uses three layers of abstraction to represent words in the hash table.
* Part of: Project 2
* December 4th, 2018 
*/ 
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <vector>
#include <sstream>

#include "Index.h"
#include "HashNode.h"
#include "Loc_Values.h"
#include "ActualNode.h"
#include "StringProcessing.h"

using namespace std;

//Constructor
Index::Index()
{
	size = 500000;
	total_elem = 0;
	table = new vector<HashNode>[size];
}

//Destructor
Index::~Index()
{
	delete []table;
}

//Function: record
//Input: Inputs a file path
//Returns: Nothing
//Does: takes a file path and stores all words in file in table
void Index::record(string file_name)
{
	ifstream infile;
	string word;
	infile.open(file_name);
	infile.clear();
	infile.seekg(0, ios::beg);
	string line;
	FileName *line_storage = new FileName();
	line_storage->filename = file_name;
	while (getline(infile, line)){
		line_storage->line_vector.push_back(line);  
		istringstream iss(line);
		while (iss >> word){
			word = input_process(word);
			string word_format = to_lower(word);	
			load_factor_check_and_expand(total_elem);
			int hash_index = hash(word_format, size);

			if (table[hash_index].empty())	
				empty_insert(word, word_format, hash_index, 
					line_storage->line_vector.size());			
			else 
				non_empty_insert(word, word_format, hash_index, 
					line_storage->line_vector.size());

			total_elem++;
		}		
	}
	aux_vector.push_back(*line_storage);
	infile.close();
}


//Function: Insert
//Inputs: string to insert,
//and line_ref which is a line location reference for a hashnode
//Outputs: Nothing
//Does: inserts a string to the hash table
void Index::insert(string word, HashNode *insert_node, vector<HashNode> *new_t)
{
	int hash_index = hash(word, size);
	
	vector<HashNode> my_vec;

	if (table[hash_index].empty()){
		my_vec.push_back(*insert_node);
		new_t[hash_index] = my_vec;
	}			
	else{
		new_t[hash_index].push_back(*insert_node);
	}
	total_elem++;
}

//Function: Insert_HashNode_test
//Inputs: No input
//Outputs: Should be two cause we are testing inserting two
//elements to the hash_table
//Does: This is a test function for our new insert function, that inserts
//nodes and not words. To see if it works we see the number of total
//elements we have in the hash table. 
int Index::insert_HashNode_Test()
{
	vector<HashNode> my_vec;
	HashNode *hash_node = new HashNode(); 
	ActualNode *actual_node = new ActualNode();
	Loc_Values *loc_val = new Loc_Values();
	loc_val->file_number = 2;
	loc_val->line_number = 3;
	actual_node->key = "hello";
	actual_node->location.push_back(*loc_val); 
	
	hash_node->key = "hello"; 	
	hash_node->vec_ptr.push_back(*actual_node);

	vector<HashNode> my_vec2;
	HashNode *hash_node2 = new HashNode(); 
	ActualNode *actual_node2 = new ActualNode();
	Loc_Values *loc_val2 = new Loc_Values();
	loc_val2->file_number = 2;
	loc_val2->line_number = 3;
	actual_node2->key = "Hello";
	actual_node2->location.push_back(*loc_val2); 
	
	hash_node2->key = "hello"; 	
	hash_node2->vec_ptr.push_back(*actual_node2);
	//insert("hello", hash_node);
	//insert("Hello", hash_node2);
	return total_elem;

}
//Function: word_Insert
//Inputs: string to insert,
//and line_ref which is a line location reference for a hashnode
//Outputs: Nothing
//Does: inserts a string to the hash table
void Index::word_Insert(string word, int line_ref)
{
	word = input_process(word);
	string word_format = to_lower(word);
	int hash_index = hash(word_format, size);
	
	if (table[hash_index].empty())	
		empty_insert(word, word_format, hash_index, line_ref);			
	else 
		non_empty_insert(word, word_format, hash_index, line_ref);
	total_elem++;
}


//Function: empty_insert
//Input: actual word, lower case rep of word(word_format), and hash index
//Returns: Nothing
//Does: inserts into an empty slot in the hash array
void Index::empty_insert(string w, string w_format, int hash_idx, int num_line)
{

	vector<HashNode> my_vec;
	HashNode *hash_node = new HashNode(); 
	ActualNode *actual_node = new ActualNode();
	Loc_Values *loc_val = new Loc_Values();
	loc_val->file_number = aux_vector.size();
	loc_val->line_number = num_line;
	actual_node->key = w; //store original word
	actual_node->location.push_back(*loc_val); 
	hash_node->key = w_format; // store lower case word		
	hash_node->vec_ptr.push_back(*actual_node);
	my_vec.push_back(*hash_node);

	table[hash_idx] = my_vec;
}

//Function: non_empty_insert
//Input: actual word, lower case rep of word(word_format), and hash index
//Returns: Nothing
//Does: inserts into a non-empty slot in the hash array
void Index::non_empty_insert(string w, string w_format, 
	int hash_idx, int num_line)
{
	for (int i = 0; i < int(table[hash_idx].size()); i++){
		if (w_format == table[hash_idx][i].key){ //looking at poster boys
			bool found = false;
			for (int j = 0; j < int(table[hash_idx][i].vec_ptr.size()); j++){
				if (w == table[hash_idx][i].vec_ptr[j].key){
					Loc_Values *loc_val = new Loc_Values();
					loc_val->file_number = aux_vector.size();
					loc_val->line_number = num_line;
					table[hash_idx][i].vec_ptr[j].location.push_back(*loc_val);
					found = true;
				}
			}
			if (!found) //didn't find actual rep
				table[hash_idx][i].vec_ptr.push_back
					(*not_found_module(aux_vector.size(), num_line, w));
		}
		else if (i == int(table[hash_idx].size())){
			HashNode *hash_node = new HashNode(); 
			ActualNode *actual_node = new ActualNode(); 
			Loc_Values *loc_val = new Loc_Values();

			hash_node->key = w_format; // store lower case word
			actual_node->key = w; //store original word
			loc_val->file_number = aux_vector.size();
			loc_val->line_number = num_line;
	
			actual_node->location.push_back(*loc_val);
			hash_node->vec_ptr.push_back(*actual_node);
			table[hash_idx].push_back(*hash_node);
		}	
	}
}

//Function: not_found_module
//Inputs:Values to be stored in an actual node, word and line number,filepath
//Outputs: An actualNode created
//Does: modularizes process in non_empty insert
ActualNode* Index::not_found_module(int aux_v, int num_line, string word)
{
	Loc_Values *loc_val = new Loc_Values();
	loc_val->file_number = aux_v;
	loc_val->line_number = num_line;

	ActualNode *actual_node = new ActualNode(); 
	actual_node->key = word; //store original word
	actual_node->location.push_back(*loc_val);
	return actual_node;
}

// Function: insensitive_search
// Inputs: string to search for 
// Returns: Returns the file_path, line number, and line
// Does: Looks through the hash table for an appearance of a word
void Index::insensitive_search(string word, ostream &out)
{
	string word_format = to_lower(word);
	int file_no, hash_index, line_no;
	hash_index = hash(word_format, size);
	bool found = false; 
	for (int i = 0; i < int(table[hash_index].size()); i++)
	{
		if(word_format == table[hash_index][i].key)
		{
			found = true;
			for (int j = 0; j < int(table[hash_index][i].vec_ptr.size()); j++){
				for (int y = 0; y < int(table[hash_index][i].vec_ptr[j]
										.location.size()); y++){
					file_no = table[hash_index][i].vec_ptr[j].
													location[y].file_number;
					line_no = table[hash_index][i].vec_ptr[j].
													location[y].line_number;
					out << aux_vector[file_no].filename << ":";
					out << line_no << ": ";
					out << aux_vector[file_no].line_vector[line_no-1] << endl;
				}
			}
			break;
		}
	}
	if (!found)
		out << endl << "Query not found." << endl;
}

//Function: sensitive_search
//Inputs: string to search for 
//Returns: Returns the file_path, line number, and line
//Does: Looks through the hash table for an appearance of an exact word
//(sensitive search)
void Index::sensitive_search(string word, ostream &out)
{
	string word_format = to_lower(word);
	int file_no, hash_index, line_no;
	hash_index = hash(word_format, size);
	bool found = false; 
	for (int i = 0; i < int(table[hash_index].size()); i++)
	{
		if(word_format == table[hash_index][i].key)
		{
			for (int j = 0; j < int(table[hash_index][i].vec_ptr.size()); j++){
				if (table[hash_index][i].vec_ptr[j].key == word){
					found = true;
					for (int y = 0; y < int(table[hash_index][i].vec_ptr[j].
													location.size()); y++){
						file_no = table[hash_index][i].vec_ptr[j].
													location[y].file_number;
						line_no = table[hash_index][i].vec_ptr[j].
													location[y].line_number;
						out << aux_vector[file_no].filename << ":";
						out << line_no << ": ";
						out << aux_vector[file_no].line_vector[line_no-1]
																 << endl;
					}
					break;		
				}
			}
			if (found == true)
				break; 
		}
	}
	if (!found)
		out << endl << "Query not found." << endl;
}


//Name: public_test_call 
//Inputs: Takes in all possible arguements for private functions
//hash_key is the word to be hashed, func_call is the function to call
//load_size is the size for the load factor check
//hash_size is the size of the hash table
//Returns: Nothing really, just cout's output in some cases
//Does: Calls private functions based on the function passed in as 
//the arguement "func_to_call"
void Index::public_test_call(string func_to_call, string hash_key, 
					int hash_size, int load_size)
{
	if (func_to_call == "hash")
		cout << hash(hash_key, hash_size);
	else if(func_to_call == "to_lower")
		cout << to_lower(hash_key);
	else if(func_to_call == "load_factor")
		cout << load_factor(load_size);
	else if(func_to_call == "L_F_C_E")
		load_factor_check_and_expand(load_size);

}

//Name: hash 
//Inputs: Takes in a string(key)
//Returns: Returns the index for the key
//Does: Computes a hash value for the inputted key
static const int P = 16908799;
size_t Index::hash(string key, int size)
{
	int hashVal = 0;
	for (size_t i = 0; i < key.length(); i++){
		hashVal = (127 * hashVal + key[i]) % P;
	}
	return hashVal % size;
}



//Name: load_factor_check_and_adjust()
//Inputs: Takes in the number of all items in storage
//Does: Takes in the number of all items in storage, determines if 
//load factor is above 75%, if it is, it calles the expand function;
//and carries out expand on the list. It also rehashes 
void Index::load_factor_check_and_expand(int input_size)
{
	if (load_factor(input_size) >= 0.75)
		expand();
}


//Name: load_factor
//Inputs: Takes in the size of the vector
//Returns: returns load factor
//Does: Calculates load factor of storage
double Index::load_factor(double input_size)
{
	return input_size / size;
}


//Name: expand
//Inputs: No inputs
//Returns: Nothing
//Does: Expands the dynamic array 
void Index::expand()
{
	size = size * 2;
	vector<HashNode> *new_ptr = new vector<HashNode>[size];
	for (int i = 0; i < size/2; i++){
		for (int j = 0; j < int(table[i].size()) ;j++){
			int hash_index = hash(table[i][j].key, size);

			vector<HashNode> my_vec;

			if (new_ptr[hash_index].empty()){
				my_vec.push_back(table[i][j]);
				new_ptr[hash_index] = my_vec;
			}			
			else{
				new_ptr[hash_index].push_back(table[i][j]);
			}
			total_elem++;
		} 
	}
	delete []table; 
	table = new_ptr;
}

//Name: to_lower
//Inputs: inputs string to convert to lowercase
//Returns: Nothing
//Does: converts whole string to lowercase
string Index::to_lower(string input)
{
  	char c;
  	string output = "";
  	for (int i = 0; i < int(input.size()); i++){
    	c=input[i];
    	output += (tolower(c));
  	}

  	return output;
}

//Name: get_size
//Inputs: No inputs
//Returns: size of hash_table
//Does: Returns the size of the hash_table
int Index::get_size()
{
	//Testing purposes.
	//cout << "this is total elements: "<< total_elem << endl;
	return size; 
}
