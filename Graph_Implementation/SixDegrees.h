/*
 * Filename: SixDegrees.h
 * Contains: Header file for SixDegrees class
 * Description: Contains function and variable declarations
 * 				of SixDegrees class
 *
 */

#ifndef SIXDEGREES_H_
#define SIXDEGREES_H_

#include <iostream>
#include <string>
#include "Actor.h"
#include "Graph.h"
#include "Stack.h"
#include "SixDegrees.h"
using namespace std; 

class SixDegrees{
	public: 
		SixDegrees();
		void populate_graph(string);
		void run(istream &, ostream &);
		void print();
		
	private: 
		Graph<Actor> hollywood; 
		Actor *arr;
		int size; 
		void add_vertice(Graph<Actor>, Stack<Actor>);
		void BFS(Actor, Actor, ostream &);
		void add_movie(Actor [], int);
		//bool actor_in(string);

	

};

#endif /* SIXDEGREES_H_ */