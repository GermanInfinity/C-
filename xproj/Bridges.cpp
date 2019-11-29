/*

Name: Bridges.cpp
Author: Akwarandu Ugo Nwachuku
Project: Euler's Konisberg bridge challenge, Graphs
Description: Bridges class implementation

*/
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Island.h"
#include "Graph.h"
#include "Stack.h"
#include "Queue.h"
#include "Bridges.h"
using namespace std; 

//Default constructor
Bridges::Bridges()
{
  //konigsberg declared as graph for this class
  arr = new Island[20] ;
  size = 0;
}

//Function: populate_graph
//Inputs: String of input file name
//Returns: does not return anything
//Does: Populates the graph 
void Bridges::populate_graph(string Island_file)
{
    Stack<Island> Island_stack; 
   	string insert_name;

   	ifstream infile; 
	  infile.open(Island_file.c_str());
    infile.clear();
   	infile.seekg(0, ios::beg);

  	while (getline(infile, insert_name)){
   		Island a(insert_name);
   		while (getline(infile, insert_name)){
   			if (insert_name != "*"){
   				a.insert_bridge(insert_name);
        }
        if (insert_name == "*")
          break;
   		}
   		Island_stack.push(a);
   	}
   	konigsberg.initialize_graph(Island_stack.get_size());
   	add_vertice(konigsberg, Island_stack);
}

void Bridges::run(istream &in, ostream &out)
{
	string name;
	string run_arr[2];
    int rot[1];
	int count = 0; 
    cout << endl;

	while (getline(in, name)){
    Island a3(name);
    if (konigsberg.is_vertex(a3) and count == 0){
        run_arr[count] = name;
        rot[0] = konigsberg.find_index(a3);
    }
    else if (count == 0) {
        cout << "Sorry, " << name << " is not in the list" << endl;
        cout << "Enter a new island." << endl;
        continue;
    }

    if (count == 1 and konigsberg.is_edge(name, rot[0]))
       run_arr[1] = name;
    else if (count == 1){
        cout << "Sorry, " << name << " bridge is not in the list";
        cout << " or connected to the starting island." << endl;
        cout << "Try again." << endl;
        continue;
    }
    count++;
    if (count == 2)
        break;
	}
	Island a1(run_arr[0]); 
    DFS(a1, run_arr[1], out);
}

//Function: BFS
//Inputs: 2 Island objects, reference to oustream
//Outputs: Shortest path
//Does: Find's the shortest path between two actors
void Bridges::BFS(Island star_actor, Island famous_actor, ostream &out)
{
	konigsberg.clear_marks();
    konigsberg.initialize_path();

    Queue<Island> queue_1, queue_2;
    Island temp;
    Island n1, n2;

    queue_1.enqueue(star_actor);
    temp = star_actor;
    while (queue_1.is_empty() == false){

        queue_1.dequeue(temp);
        konigsberg.get_to_vertices(temp, queue_2);
        
        while (queue_2.is_empty() == false){
            queue_2.dequeue(n1);
            konigsberg.update_predecessor(temp, n1);

            if (famous_actor == n1)
                break;
            else
                queue_1.enqueue(n1);
        }

        if (famous_actor == n1)
            break;  
    }
    
    konigsberg.report_path(out, star_actor, famous_actor);
}

//Function: DFS
//Inputs: 2 Island objects, reference to oustream
//Outputs: Longest path
//Does: Tries to reach all vertices in konigsberg
void Bridges::DFS(Island start_island, string bridge, ostream &out)
{
    Stack<string> bridges; //bridges crossed stack. 
    Stack<Island> islands;
    Queue<Island> queue_1; //neighbour
    konigsberg.clear_marks();
    konigsberg.initialize_path();
    Island n1, result;
    srand (time(NULL));

    result = konigsberg.connect(start_island, bridge); 
    bridges.push(bridge);
    islands.push(result);

    cout << endl;
    int c;
    konigsberg.get_to_vertices(result, queue_1); 

    while (bridges.get_size() < 15)
    {
        string edge = konigsberg.get_edge(queue_1.top(), result);
        
        if (edge.size() == 2)
        {
            char q = edge[0];
            char a = edge[0];
            string b(1, a);
            if (q == 'q' and bridges.in_stack(b))
                edge = "p";
            else if (q == 'q' and !bridges.in_stack(b))
                edge = "q";

            if (q == 's' and bridges.in_stack(b))
                edge = "r";
            else if (q == 's' and !bridges.in_stack(b))
                edge = "s";
        }

        if (bridges.in_stack(edge))
        {

            if (islands.in_stack(queue_1.top()))
            {
                queue_1.dequeue(n1);
                continue;
            }
            else 
            {
                cout << endl << "The Sheriff catches you and sees that you are trying to cross a bridge again!" << endl;
                cout << "'That's it', he says, 'you're out of town. Come back later!'" << endl; 
                break;
            }
        }
        
        
        else if(!bridges.in_stack(edge))
        {
            bridge = konigsberg.get_edge(queue_1.top(), result); 
            if (bridges.get_size() == 1)
                cout << "You ended up at " << result << endl; 

            if (bridge.size() == 2)
            {
                if(rand() % 10 <= 5){
                    char b = bridge[0];
                    string passed_bridge(1, b);
                    bridges.push(passed_bridge);
                    islands.push(result);
                    Island curr_island = result;
                    result = konigsberg.connect(curr_island, passed_bridge);
                    cout << "You then used " << passed_bridge << " to get to " << result << endl; 
                    konigsberg.get_to_vertices(result, queue_1); 
                    queue_1.dequeue(n1);
                }
                else{ 
                    char b = bridge[1];
                    string passed_bridge(1, b);
                    bridges.push(passed_bridge);
                    islands.push(result);
                    Island curr_island = result; 
                    result = konigsberg.connect(curr_island, passed_bridge); //should be long island that goes in here 
                    cout << "You then used " << passed_bridge << " to get to " << result << endl; 
                    konigsberg.get_to_vertices(result, queue_1); 
                    queue_1.dequeue(n1);
                }
            }
            
            
            else 
            {   
                bridges.push(bridge);
                islands.push(result);
                Island curr_island = result;
                result = konigsberg.connect(curr_island, bridge);
                cout << "You then used " << bridge << " to get to " << result << endl; 
                konigsberg.get_to_vertices(result, queue_1); 
                queue_1.dequeue(n1);
            }    
        }
    }
}


//Function: add_vertice
//Inputs: Empty graph, Stack of actors
//Returns: does not return anything
//Does: add_vertice populates the konigsberg graph and makes an array of 
//      actors, the array is then sent to the add_edge function which 
//      adds the edge 
void Bridges::add_vertice(Graph<Island> actor_graph, Stack<Island> stack_of_actors)
{
    int count = 0; 
    size = stack_of_actors.get_size();
    Island arr[size];

    while(stack_of_actors.is_empty() == false){
        Island a1;
        a1 = stack_of_actors.top();
        konigsberg.add_vertex(a1);
        stack_of_actors.pop();
        arr[count] = a1;
        count++;
	  }
    add_bridge(arr, size);
}

//Function: add_bridge
//Inputs: Array of actors
//Returns: does not return anything
//Does: Modifies graph to add edges
void Bridges::add_bridge(Island arr[], int size)
{
    for (int x = 0; x < size; x++){
        for (int y = 0; y < size; y++){
            if (x != y ){  
                string similar_bridge = arr[x].connect(arr[y]);
                //cout << similar_bridge << endl;
                if (similar_bridge != "")
                {
                    konigsberg.add_edge(arr[x], arr[y], similar_bridge);
                }
            }
         }
    }
}

//Function: print
//Inputs: Nothing
//Returns: Nothing
//Does: Calls graph's print function
void Bridges::print()
{
  konigsberg.print_matrix(cout);
}

//idea is, we are comparing actors in the graph, 
	//with actors in an actor in the stack, 
	//checking if they have any connection
	//if they do, make an edge with the movie they have in common
	//if not just add to the graph.

template class Graph<Island>;
template class Graph<int>;
template class Graph<char>;
template class Graph<string>;
