/*
 * BinarySearchTree.h
 *
 *  Created on: Oct 23, 2018
 */

#ifndef TRIE_H_
#define TRIE_H_

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct Node {
    char   data;
    Node *A;
    Node *C;
    Node *G;
    Node *T;
    bool eow;
};
class Trie{
public: 
	Trie(); //Default constructor
	~Trie(); //
	void insert_sequence(string); //Function call to insert a sequence
	void print() const; //Print function that accepts root
	void post_order_print() const; //post order print function that works
	string query(string); //Query wrapper function
	string remove(string); // my remove function
	void manager(char, string, ofstream &); //Manager function

private:
	//How to know which functions should be private or public? 

	Node *root; //Root of the tree starts at NULL.
	int i; //counter for remove
	int match; //match for how many characters we have matched.
	int depth; //Depth for the length of how far we are going in the trie
	bool complete; //Boolean for if we have completed matching
	double max_ratio; //Max ratio fo matches
	bool remove_with_no_delete; //Boolean for removing with no delete
	string seq;//string for concatenating matched sequences
	void post_order_delete(Node *); //Deletes in post-order fashion.


	void insert_sequence(Node *, string); //Inserts a sequence.
	void recursive_insert(Node *, string); //Inserting a question mark.
	Node *insert_now(char); //Creates a node to be inserted.
	Node *make_root(); //Creates a root node
	void four_nodes(Node *node); //Creates four nodes for the question mark
	void four_nodes_eow(Node *, string); //Marks end of word 
	void node_A(Node *, string); //Handles insert for A
	void node_C(Node *, string); //Handles insert for C
	void node_T(Node *, string); //Handles insert for G
	void node_G(Node *, string); //Handles insert for T
	void node_que(Node *, string); //Handles insert for ?


	bool remove(Node *, string, int); //New remove function.
	bool base_case(Node *);  //Base case code for remove
	bool is_child_in_trie(Node *); //Function for checking if child in trie
	bool delete_node(Node *); //Deletes node
	bool node_eow_change(Node *); //Changes end of word value

	double query_this(Node *, string, int, int, bool, int, string, string &);//, string &);//query function
	string shortest_sequence(Node *, string); //function that returns string of 
											//shortest sequence
	void query_normal(Node *, string, int, int, bool, int, string, string &);
	double query_check(Node *, string, int, int, bool, int, string, string &);
	double no_more_match(Node *, string, int, int, bool, int, string, string &);
	// Querys character A 
	void queryA(Node *, string, int, int, bool, int, string, string &); 
	// Querys character C 
	void queryC(Node *, string, int, int, bool, int, string, string &);
	// Querys character G  
	void queryG(Node *, string, int, int, bool, int, string, string &); 
	// Querys character T 
	void queryT(Node *, string, int, int, bool, int, string, string &); 

	//helper functions for finding the shortest sequence
	string tie_breaker(string, int, char, string, string, string, string, int);
	string index_string(int, char, string, string, string, string);
	string best_finder(size_t list[], string, string, string, string);

	int tree_height(Node *node) const; //returns tree height, used in 
										//query function
	int shortest_path(Node *node, string, int); //gets shortest path to 
												//bottom of the trie
	bool in_tree(char a, Node *node); //short boolean function to check 
										//if character is in tree

	Node *&node_finder(char, Node *); //This function returns the node 
										//child we want to go into.
	Node *&parent_child(Node *, Node *); //This function returns the parent 
	                                    //pointer to the child with data
	void EOW_marker(Node *, int);  //EOW marker function
	void print(Node *, string) const; //Post order print function
	void post_order_print(Node *) const; //my post order print function
};

#endif /* TRIE_H_ */