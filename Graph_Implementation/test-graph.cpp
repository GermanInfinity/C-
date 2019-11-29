/*

Author: Akwarandu Ugo Nwachuku
Project: Homework 5, Graphs
Description: unit test file

*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Actor.h"
#include "SixDegrees.h"
using namespace std; 

void Actor_test();
 
int main(int argc, char*argv[]) 
{
	SixDegrees graph_test;
	ifstream infile;
	graph_test.populate_graph("actors.txt");
	graph_test.print();

	if (argc == 1){
		
    	cout << "Enter two actor names separated by a new line." << endl;
    	graph_test.run(cin, cout); 
    }

    else if (argc == 2){
    	infile.open(argv[1]); //supposed to be input file. 

    	infile.clear();
    	infile.seekg(0, ios::beg);

    	if (!infile.is_open()){
    		cerr << "Input file could not open." << endl;
    		return -1;
    	}
    	while (infile)
    		graph_test.run(infile, cout);
    	infile.close();

    	return 0;

    }
    
	/*The basic testing for my graph was to add actors from my actor
	text file to the graph, and visually check to see if the shortest 
	distance is printed out to the console. Other than that, I test the Actor
	class I wrote.*/
	//Actor_test();

	//Graph Tests
	// SixDegrees second_graph_test;
	// second_graph_test.populate_graph("actors.txt");
	// SixDegrees third_graph_test = second_graph_test; //Copy constructor test
	// second_graph_test.print();

	// SixDegrees fourth_graph_test;
	// fourth_graph_test.populate_graph("actor_file_test.txt");
	// second_graph_test = fourth_graph_test; //Assignment operator test
	// second_graph_test.print();

	//Testing a graph of ints; 
	graph_test.populate_graph("graph_ints.txt");
	graph_test.print();
	return 0;
}


void Actor_test()
{
	cout << " What do you know about that" << endl; 
	
	Actor a1, a2, a3; 
	a1.insert_movie("Passion of the Christ");
	a1.insert_movie("Resevoir Dogs");
	a1.insert_movie("Bet 365");

	a2.insert_movie("The Chaingang of 1974");
	a2.insert_movie("Resevoir Dogs");

	a3.insert_movie("Haunted");
	a3.insert_movie("Resevoir Dogs");
	a3.insert_movie("The Following");

	cout << "Is Actor a3 in The Following: " << a3.in_movie("The Following") << endl;
	cout << "Is Actor a2 in Resevoir Dogs: " << a3.in_movie("Resevoir Dogs") << endl;
	cout << "Is Actor a1 in Bet 365: " << a3.in_movie("Bet 365") << endl;

	cout << "a3 and a2 acted in " << a3.connect(a2) << " together." << endl;
	cout << "a3 and a1 acted in " << a3.connect(a1) << " together." << endl;
	cout << "a2 and a1 acted in " << a2.connect(a1) << " together." << endl;
}

