/* Akwarandu Ugo Nwachuku 
* Filename: FSTreeTraversal_test.cpp
* Contains: Test driver for hash table class and functions used to 
* build hash table. 
* Part of: Project 2
* December 4th, 2018 
*/ 
#include <iostream>
#include "FSTree.h"
#include "Index.h"
#include "DirNode.h"
#include "StringProcessing.h"
using namespace std;

void run(istream &, ostream &, Index &);
void get_files(DirNode *, string, vector<string>&);
void get_files_test(string);
void simple_insert_test();
void expand_insert_test();
void hash_function_test();
void hash_table_size_test();
void hash_load_factor_test();
void hash_to_lower_test();
void hash_load_factor_test();


//Function: main
//Inputs: command line arguements
//Returns: Nothing
//Does: Takes in a file and sends it to record in the hash table
int main(int argc, char*argv[]) 
{
	Index index_build;
	//string input_file = argv[1];
	string input_file = "/h/anwach01/comp15/proj2/test-dirs/mediumGutenberg";
	string start_path = input_file;
	try{
		FSTree adam(input_file);
		vector<string> files;
		get_files(adam.getRoot(), start_path, files);
		for (int i = 0; i < int(files.size()); i++)
			index_build.record(files[i]);
		run(cin, cout, index_build);
	}
	catch(std::runtime_error E){ 
		cout << "Could not build index, exiting." << endl;
	}
	(void)argc;
	/**HASH TABLE TESTS**/
	//Simple insert tests my Hash table search functions. 
	//Since they both complement each other they could both confirm
	//functionality. 
	//simple_insert_test();
	//hash_function_test(); Works.
	//hash_table_size_test(); Works. 
	//hash_to_lower_test(); Works. 
	//hash_load_factor_test(); Works.
	//simple_insert_test(); Works.
	//cout << index_build.insert_HashNode_Test(); Works.
	//expand_insert_test();
	//index_build.get_size();
}



//Function: run
//Inputs: istream object ostream object and hash table object
//Outputs: nothing
//Does: behaves just like grep on the command line, queries database
//based on users input
void run(istream &in, ostream &out, Index &index)
{
	string input;
	out << "Query?" << endl;
	while (getline(in, input))
	{
		if (input[0] == '@' and input[1] == 'q'){
			out << "Goodbye! Thank you and have a nice day." << endl;
			break;
		}
		else if (input[0] == '@' and input[1] == 'i'){ 
			input = input_process(input.substr(2, -1));
			index.insensitive_search(input, out);
			out << endl << "Query?" << endl;
			continue;
		}
		else 
		{
			input = input_process(input);
			index.sensitive_search(input, out);
			out << endl << "Query?" << endl;
			continue;
		}
	}
}


//Function: get_files
//Inputs: Root node of a directory
//Outputs: nothing
//Does: prints file names
void get_files(DirNode *node, string path , vector<string>& files)
{
	string temp = path;
	string sec_temp = path;
	if (node->hasFiles()){
	   for (int x = 0; x < node->numFiles(); x++){
	   	path = path + "/" + node->getFile(x);
		files.push_back(path);
		path = temp;
		}
	}

	if (node->hasSubDir())
		for (int x = 0; x < node->numSubDirs(); x++){
			path = temp + "/" + node->getSubDir(x)->getName();
			get_files(node->getSubDir(x), path, files);
		}
}


//Function: simple_index_class_test
//Inputs: Nothing
//Outputs: Nothing
//Does: inserts words into the hashtable and 
//checks for case sensitive and insensitive searches
void simple_insert_test()
{
	//*** Hash class(Index class) test ***//
	Index hash_table_test;
	hash_table_test.word_Insert("Jack", 1);
	hash_table_test.word_Insert("jack ", 1);
	hash_table_test.word_Insert("Jill ", 1);
	hash_table_test.word_Insert("went ", 1);
	hash_table_test.word_Insert("up ", 1);
	hash_table_test.word_Insert("the ", 1);
	hash_table_test.word_Insert("hill.", 1);
	hash_table_test.word_Insert("  ", 1);
	hash_table_test.word_Insert("HILL ", 1);
	hash_table_test.word_Insert("HILL ", 1);
	hash_table_test.word_Insert("hiLL", 1);

	//Testing sensitive search, insensitive search
	//Test     ::: output
	//hash_table_test.insensitive_search("Jack", cout);
	// hash_table_test.insensitive_search("jack", cout);
	// hash_table_test.sensitive_search("jiLL", cout);
	// hash_table_test.sensitive_search("hill", cout);
	// hash_table_test.insensitive_search("HILL", cout);
	//@i Jack     ::: 2 occurences
	//@i jack     ::: 1 occurence
	//   jiLL     ::: Not found
	//   hill     ::: Not found...because not sanitized!
	//   HILL     ::: 1 occurence
}

//Function: expand_index_class_test
//Inputs: Nothing
//Outputs: Nothing
//Does: inserts words into the hashtable and 
//checks for case sensitive and insensitive searches
//after expanding
void expand_insert_test()
{
	Index hash_test;
	hash_test.public_test_call("L_F_C_E", "Hello", 5, 500000);
}

//Function: hash_function_test
//Inputs: file to be tested
//Outputs: Nothing
//Does: Inserts ten words into the hash function, and sees tha it returns
//a number that's modulo of the inputted size. This is how the test
//confirms hash works. (If the printed output is modulo of the given size)
void hash_function_test()
{
	Index hash_test;
	hash_test.public_test_call("hash", "Hello", 5, 0);
	hash_test.public_test_call("hash", "Hello", 5, 0);
	hash_test.public_test_call("hash", "Hello", 5, 0);
	//expecting some index values less than 5.
	//These all hashed to the same position, as expected and
	//position index was lower than 5: it was 4. 
}

//Function: hash_table_size_test
//Inputs: No input
//Output: No output
//Does: Tests the get size function in the hash table class
void hash_table_size_test()
{
	Index hash_test;
	cout << hash_test.get_size() << endl;
	//This printed out the expected output size of the table, 
	//which was the set initial number: 500000. 
}

//Function: hash_to_lower_test
//Inputs: No input
//Output: No output
//Does: Tests the to_lower function in the hash table class
void hash_to_lower_test()
{
	Index hash_test;
	hash_test.public_test_call("to_lower", "COUT LOWER_CASE", 0, 0);
	//expected output: cout lower_case
	//posterior output: cout lower_case
}

//Function: hash_load_factor_test
//Inputs: No input
//Output: No output
//Does: Tests the load_factor function in the hash table class
void hash_load_factor_test()
{
	Index hash_test;
	hash_test.public_test_call("load_factor", "", 0, 20000);
	//Caught an error. False data type division. Changed data type to 
	//double. 
	//Fixed! Output - 0.04
}

//Function: get_files
//Inputs: file to be tested
//Outputs: Nothing
//Does: cout's all the files in a directory
void get_files_test(string inp_file)
{
	string input_file = inp_file;
	string start_path = input_file;
	FSTree test_direc(input_file);
	vector<string> test_files;
	get_files(test_direc.getRoot(), start_path, test_files);
	
	for (int i = 0; i < int(test_files.size()); i++){
		cout << test_files[i] << endl;
	}
}