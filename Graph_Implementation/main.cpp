/*
 * Filename: main.cpp
 * Contains: Driver for homework 5 
 * Description: Populates a graph and runs BFS on it
 *
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "SixDegrees.h"
#include "Actor.h"

using namespace std;

int main(int argc, char*argv[]) 
{
    ifstream infile;
    SixDegrees sd;
    sd.populate_graph("actor_file_test.txt");
    sd.print();
    if (argc == 1){
    	cout << "Enter two actor names separated by a new line." << endl;
    	sd.run(cin, cout); 
    }

    else if (argc == 2){
    	infile.open(argv[1]);

    	infile.clear();
    	infile.seekg(0, ios::beg);

    	if (!infile.is_open()){
    		cerr << "Input file could not open." << endl;
    		return -1;
    	}
        
        cout << "Enter two actor names separated by a new line." << endl;
        cout << "Press ctrl-D to quit" << endl; 
    	while (infile)
    		sd.run(infile, cout);
    	infile.close();
    	return 0;

    }
    return 0;
}
