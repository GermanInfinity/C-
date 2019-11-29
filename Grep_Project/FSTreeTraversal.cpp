/* Akwarandu Ugo Nwachuku 
* Filename: FSTreeTraversal_test.cpp
* Contains: main Driver for gerp implementation. 
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



//Function: main
//Inputs: command line arguements
//Returns: Nothing
//Does: Takes in a file and sends it to record in the hash table
int main(int argc, char*argv[]) 
{
	Index hash_table;
	string input_file = argv[1];
	string start_path = input_file;

	try
	{
		FSTree adam(input_file);
		vector<string> files;
		get_files(adam.getRoot(), start_path, files);
		for (int i = 0; i < int(files.size()); i++)
			hash_table.record(files[i]);
		run(cin, cout, hash_table);
	}
	catch(std::runtime_error E)
	{ 
		cout << "Could not build index, exiting." << endl;
	}

	(void)argc;


	return 0;
}


//Function: run
//Inputs: istream object ostream object and hash table object
//Outputs: nothing
//Does: behaves just like grep on the command line, queries database
//based on users input
void run(istream &in, ostream &out, Index &index)
{
	string input;
	out << "Query? ";
	while (getline(in, input))
	{
		if (input[0] == '@' and input[1] == 'q'){
			out << "Goodbye! Thank you and have a nice day." << endl;
			break;
		}
		else if (input[0] == '@' and input[1] == 'i'){ 
			input = input_process(input.substr(2, -1));
			index.insensitive_search(input, out);
			out << "Query? ";
			continue;
		}
		else 
		{
			input = input_process(input);
			index.sensitive_search(input, out);
			out << "Query? ";
			continue;
		}
	}
}


// Function: get_files
// Parameters: DirNode pointer, a string path 
// Returns: nothing
// Does: Get's the files from a given file path
void get_files(DirNode *node, string path, vector<string>& files)
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
