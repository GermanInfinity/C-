/*
 * Filename: SixDegrees.h
 * Contains: Header file for SixDegrees class
 * Description: Contains function and variable declarations
 * 				of SixDegrees class
 *
 */

#ifndef BRIDGES_H_
#define BRIDGES_H_

#include <iostream>
#include <string>
#include "Island.h"
#include "Graph.h"
#include "Stack.h"

using namespace std; 


class Bridges{
	public: 
		Bridges();
		void populate_graph(string);
		void run(istream &, ostream &);
		void print();
		
	private: 
		Graph<Island> konigsberg; 
		Island *arr;
		int size; 
		void add_vertice(Graph<Island>, Stack<Island>);
		void BFS(Island, Island, ostream &); //Runs breadth first search
		void DFS(Island, string, ostream &); //Runs depth first search
		void add_bridge(Island [], int);
		//bool actor_in(string);

	

};

#endif /* BRIDGES_H_ */