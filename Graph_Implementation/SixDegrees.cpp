/*

Name: SixDegrees.cpp
Author: Akwarandu Ugo Nwachuku
Project: Homework 5, Graphs
Description: SixDegrees class implementation

*/
#include <iostream>
#include <fstream>
#include <string>
#include "Actor.h"
#include "Graph.h"
#include "Stack.h"
#include "Queue.h"
#include "SixDegrees.h"
using namespace std; 

//Default constructor
SixDegrees::SixDegrees()
{
  //hollywood declared as graph for this class
  arr = new Actor[20] ;
  size = 0;
}

//Function: populate_graph
//Inputs: String of input file name
//Returns: does not return anything
//Does: Populates the graph 
void SixDegrees::populate_graph(string actor_file)
{
    Stack<Actor> actor_stack; 
   	string insert_name;

   	ifstream infile; 
	  infile.open(actor_file.c_str());
    infile.clear();
   	infile.seekg(0, ios::beg);

  	while (getline(infile, insert_name)){
   		Actor a(insert_name);
   		while (getline(infile, insert_name)){
   			if (insert_name != "*"){
   				a.insert_movie(insert_name);
        }
        if (insert_name == "*")
          break;
   		}
   		actor_stack.push(a);
   	}
   	hollywood.initialize_graph(actor_stack.get_size());
   	add_vertice(hollywood, actor_stack);
}

void SixDegrees::run(istream &in, ostream &out)
{
	string name;
	string run_arr[2];
	int count = 0; 

	while (getline(in, name)){
    Actor a3(name);
    if (hollywood.is_vertex(a3))
        run_arr[count] = name;
    else 
    {
        cout << "Sorry, " << name << " is not in the list" << endl;
        cout << endl;
        continue;
    }
		count++; 
		if (count == 2) break;
	}
	Actor a1(run_arr[0]); 
	Actor a2(run_arr[1]);

  if (hollywood.is_vertex(a1) and hollywood.is_vertex(a2))
    BFS(a1, a2, cout); 
}

void SixDegrees::BFS(Actor star_actor, Actor famous_actor, ostream &out)
{
	  hollywood.clear_marks();
    hollywood.initialize_path();

    Queue<Actor> queue_1, queue_2;
    Actor temp;
    Actor n1, n2;

    queue_1.enqueue(star_actor);
    temp = star_actor;
    while (queue_1.is_empty() == false){

        queue_1.dequeue(temp);
        hollywood.get_to_vertices(temp, queue_2);
 
        while (queue_2.is_empty() == false){
            queue_2.dequeue(n1);
            hollywood.update_predecessor(temp, n1);

            if (famous_actor == n1)
                break;
            else
                queue_1.enqueue(n1);
        }

        if (famous_actor == n1)
            break;  
    }
    
    hollywood.report_path(out, star_actor, famous_actor);
}

//Function: add_vertice
//Inputs: Empty graph, Stack of actors
//Returns: does not return anything
//Does: add_vertice populates the hollywood graph and makes an array of 
//      actors, the array is then sent to the add_edge function which 
//      adds the edge 
void SixDegrees::add_vertice(Graph<Actor> actor_graph, Stack<Actor> stack_of_actors)
{
    int count = 0; 
    size = stack_of_actors.get_size();
    Actor arr[size];

    while(stack_of_actors.is_empty() == false){
        Actor a1;
        a1 = stack_of_actors.top();
        hollywood.add_vertex(a1);
        stack_of_actors.pop();
        arr[count] = a1;
        count++;
	  }
    add_movie(arr, size);
}

//Function: add_movie
//Inputs: Array of actors
//Returns: does not return anything
//Does: Modifies graph to add edges
void SixDegrees::add_movie(Actor arr[], int size)
{
    for (int x = 0; x < size; x++){
        for (int y = 0; y < size; y++){
            if (x != y ){
                string similar_movie = arr[x].connect(arr[y]);
                if (similar_movie != "")
                    hollywood.add_edge(arr[x], arr[y], similar_movie);
            }
         }
    }
}

//Function: print
//Inputs: Nothing
//Returns: Nothing
//Does: Calls graph's print function
void SixDegrees::print()
{
  hollywood.print_matrix(cout);
}

//idea is, we are comparing actors in the graph, 
	//with actors in an actor in the stack, 
	//checking if they have any connection
	//if they do, make an edge with the movie they have in common
	//if not just add to the graph.
