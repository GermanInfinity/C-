/*
 *
 * Filename: search-campus.cpp
 * Contains: Driver for lab 9, BFS for the Tufts campus 
 * Part of: Lab 9 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 */


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Graph.h"
#include "Stack.h"
#include "Queue.h"
using namespace std;

const int NUM_BUILDINGS = 15;

void populate_graph_from_file(char *, Graph<string> &);
void BFS(Graph<string> &, string, string);

// Function: main
// Parameters: integer and string
// Returns: integer
// Does: main driver: reads filcname given by parameter
//       asks for start and end destinations and runs BFSon graph
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Error. This program needs one parameter. Execute using: ./search [inputfile]\n";
        return 1;
    }

    Graph<string> g(NUM_BUILDINGS);
    populate_graph_from_file(argv[1], g);

    string start, end;
    cout << "Where are you starting from?\n";
    cin >> start;
    while (!g.is_vertex(start))
    {
        cout << "Never heard of it. Enter again, please\n";
        cin >> start;
    }

    cout << "Where are you going to?\n";
    cin >> end;
    while (!g.is_vertex(end))
    {
         cout << "No such place. Enter again, please\n";
         cin >> end;
    }

    cout << "\nHow to get there:\n";
    BFS(g, start, end);

    return 0;
}

// Function populate_graph_from_file
// Parameters: char *filename of adjacency matrix, Graph of strings (ref)
// Returns: void
// Does: creates one vertex for each building
//       and one edge for each non-zero entry in adjacency matrix
void populate_graph_from_file(char *filename, Graph<string> &g)
{
    ifstream infile;
    infile.open(filename);
    if (!infile.is_open())
    {
        cerr << "Could not open " << filename << " for reading\n";
        exit(1);
    }

    string buildings[NUM_BUILDINGS];
    string v;

    for (int i = 0; i < NUM_BUILDINGS; i++)
    {
        infile >> v;
        buildings[i] = v;
        g.add_vertex(v);
    }

    for (int i = 0; i < NUM_BUILDINGS; i++)
    {
        infile >> v;
        for (int j = 0; j < NUM_BUILDINGS; j++)
        {
            int edge_weight;
            infile >> edge_weight;
            if (edge_weight > 0)
                g.add_edge(v, buildings[j], edge_weight);
        }
    }
    infile.close();
}


// Function populate_graph_from_file
// Parameters: graph, start node and end node
// Returns: void
// Does: searches for a shortest path from start to end
//       using BFS and reports the path found (if any)
//       you can assume that the path always exists
void BFS(Graph<string> &g, string start, string end)
{
    g.clear_marks();
    g.initialize_path();

    Queue<string> queue_1, queue_2;
    string temp;
    string n1, n2;

    queue_1.enqueue(start);
    temp = start;
    while (queue_1.is_empty() == false){

        queue_1.dequeue(temp);
        g.get_to_vertices(temp, queue_2);
 
        while (queue_2.is_empty() == false){
            queue_2.dequeue(n1);
            g.update_predecessor(temp, n1);

            if (end == n1)
                break;
            else
                queue_1.enqueue(n1);
        }

        if (end == n1)
            break;

        
    }
    
    // Report path if one exists.
    g.report_path(cout, start, end);

}


