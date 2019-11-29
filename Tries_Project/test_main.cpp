/*
 * main.cpp
 *
 *  Created on: Oct 23, 2018
 *      Author: Ugo Nwachuku
 *    
 * This is a unit test file for my three functions, insert 
 * query and remove. I did most of my testing with this file, 
 * I did some more testing in my main cpp as well, and recorded
 * my results there. 
 */

#include <iostream>
#include <string> 
#include <fstream>
#include "Trie.h"
using namespace std;

void insert_test(Trie tst, ifstream infile, char a, string sequence)
{
	ofstream testfile;
	testfile.open("output_test");
	while (infile >> a >> sequence)
	{
		if (a == 'i')
			tst.insert_sequence(sequence);
		if (a == 'r')
			testfile << tst.remove(sequence) << endl;
	}
	testfile.close();
}

int main()
{
	//test file, driver, output file(output from test file)
	string sequence;
    char a;
	Trie tst;
	ifstream infile;
	ofstream testfile;

	infile.open("sequence");
	//testfile.open("output_test");

	infile.clear();
    infile.seekg(0, ios::beg);
    //insert_test(tst, infile, a, sequence);

	while (infile >> a >> sequence)
	{
		if (a == 'i')
		{
			tst.insert_sequence(sequence);
		}
		if (a == 'r')
		{
			cout << tst.remove(sequence) << endl;
		}
		if (a == 'q')
			cout << tst.query(sequence) << endl;
	}
	
	//testfile.close();
	cout << endl;
	cout << "Done reading file, output: " << endl;


	tst.post_order_print();
	tst.print();

	cout << endl;
	cout << " Excellent." << endl;
	return 0; 

}


