/*
 * Akwarandu Ugo Nwachuku
 * 17/October/2018
 * COMP 15 HW4
 * This is essentially the interface for the Trie class. 
 * It is capable of inserting and storing a sequence, querying the 
 * database for a sequence, and also removing a sequence from the 
 * database. 
 */

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cctype>
#include <string>
#include <limits>
#include <sstream>
#include <iomanip>

#include "Trie.h"

using namespace std;

//Default constructor
//My default constructor creates all the variables that are required through
//out my code. 
Trie::Trie()
{
    root = NULL;
    i = 0;
    match = 0;
    depth = 0;
    complete = false; 
    remove_with_no_delete = false; 
    max_ratio = 0;
    seq = "";

}

//Destructor
Trie::~Trie()
{
	post_order_delete(root);
}

// Function: post_order_delete
// Inputs: Pointer to a node
// Returns: Does not return anything
// Does: Deletes the trie in a post-order manner, used by the 
// destructor and when the remove function wants to delete a whole subtree
void Trie::post_order_delete(Node *node)
{
	if (node == NULL)
		return; 
	post_order_delete(node->A);
	post_order_delete(node->C);
	post_order_delete(node->G);
	post_order_delete(node->T);
	delete node;
}

// Function: insert_sequence
// Inputs: The sequence to be inserted
// Returns: Does not return anything
// Does: Takes in a string of characters and inserts them into the trie,
// but this is the wrapper function to the actual function that does that
void Trie::insert_sequence(string sequence) 
{
	if (root == NULL)
		root = make_root();
	return insert_sequence(root, sequence);
}


//Function inserts sequence to trie. I
void Trie::insert_sequence(Node *new_node, string sequence)
{
	if (sequence == "")
		return;
	if (in_tree(sequence[0], new_node)){
		char sq = sequence[0];
	    sequence = sequence.substr(1, -1);
	    EOW_marker(new_node, int(sequence.size()));
		insert_sequence(node_finder(sq, new_node), sequence);
		return;
	}
	else{
		if (sequence[0] == 'A'){
			node_A(new_node, sequence);
			return;
		}
		if (sequence[0] == 'C'){
			node_C(new_node, sequence);
			return;
		}
		if (sequence[0] == 'G'){
			node_G(new_node, sequence);
			return;
		}
		if (sequence[0] == 'T'){
			node_T(new_node, sequence);
			return;
		}
		if (sequence[0] == '?'){
			node_que(new_node, sequence);
			return;
		}
	}
}

// Function: node_A
// Inputs: Node pointer and a string sequence
// Returns: Does not return anything
// Does: This function extrapolates the insertion of A into the Trie, 
// it assigns a new node, checks if it's the end of the sequence, and
// reduces the sequence size. 
void Trie::node_A(Node *node, string sequence)
{
	node->A = insert_now(sequence[0]);
	sequence = sequence.substr(1, -1);
	EOW_marker(node->A, int(sequence.size()));
	insert_sequence(node->A, sequence);
}

// Function: node_C
// Inputs: Node pointer and a string sequence
// Returns: Does not return anything
// Does: This function extrapolates the insertion of C into the Trie, 
// it assigns a new node, checks if it's the end of the sequence, and
// reduces the sequence size. 
void Trie::node_C(Node *node, string sequence)
{
	node->C = insert_now(sequence[0]);
	sequence = sequence.substr(1, -1);
	EOW_marker(node->C, int(sequence.size()));
	insert_sequence(node->C, sequence);
}

// Function: node_G
// Inputs: Node pointer and a string sequence
// Returns: Does not return anything
// Does: This function extrapolates the insertion of G into the Trie, 
// it assigns a new node, checks if it's the end of the sequence, and
// reduces the sequence size. 
void Trie::node_G(Node *node, string sequence)
{
	node->G = insert_now(sequence[0]);
	sequence = sequence.substr(1, -1);
	EOW_marker(node->G, int(sequence.size()));
	insert_sequence(node->G, sequence);
}

// Function: node_T
// Inputs: Node pointer and a string sequence
// Returns: Does not return anything
// Does: This function extrapolates the insertion of T into the Trie, 
// it assigns a new node, checks if it's the end of the sequence, and
// reduces the sequence size. 
void Trie::node_T(Node *node, string sequence)
{
	node->T = insert_now(sequence[0]);
	sequence = sequence.substr(1, -1);
	EOW_marker(node->T, int(sequence.size()));
	insert_sequence(node->T, sequence);
}

// Function: node_que
// Inputs: Node pointer and a string sequence
// Returns: Does not return anything
// Does: This function extrapolates the insertion of ? into the Trie, 
// it assigns new nodes, checks if it's the end of the sequence, and
// reduces the sequence size. 
void Trie::node_que(Node *node, string sequence)
{
	four_nodes(node);
	sequence = sequence.substr(1, -1);
	four_nodes_eow(node, sequence);
	recursive_insert(node, sequence);
}

// Function: recursive_insert
// Inputs: A node pointer and a string
// Returns: Does not return anything
// Does: Recursively calls insert on all nodes 
void Trie::recursive_insert(Node *node, string sequence)
{
	insert_sequence(node->A, sequence);
	insert_sequence(node->C, sequence);
	insert_sequence(node->G, sequence);
	insert_sequence(node->T, sequence);	
}
// Function: four_nodes
// Inputs: A node pointer 
// Returns: Does not return anything
// Does: Assigns node pointers to newly created nodes
void Trie::four_nodes(Node *node)
{
	node->A = insert_now('A');
	node->C = insert_now('C');
	node->G = insert_now('G');
	node->T = insert_now('T');
}

// Function: four_nodes_eow
// Inputs: A node pointer 
// Returns: Does not return anything
// Does: This function checks if we are at the last character in the
// sequence, if so, it assigns an end of word marker
void Trie::four_nodes_eow(Node *node, string sequence)
{
	EOW_marker(node->A, int(sequence.size()));
	EOW_marker(node->C, int(sequence.size()));
	EOW_marker(node->G, int(sequence.size()));
	EOW_marker(node->T, int(sequence.size()));
}

// Function: make_root
// Inputs: No input
// Returns: Returns the root pointer
// Does: Makes an entire new node struct for the root, initializes all
// it's A, C, T, G pointers to null and sets root to point to the new node
Node *Trie::make_root()
{
	Node *node = new Node;
	root = node;
    root->A = NULL;
    root->C = NULL;
    root->G = NULL; 
    root->T = NULL;
    root->data = 'R';
    root->eow = false;
    return root;
}

// Function: insert_now
// Inputs: takes in a character in a sequence
// Returns: Returns a pointer to a newly created node
// Does: This function creates a new node with the desired character
// It is used for newly inserted sequences. 
Node *Trie::insert_now(char sequence_char)
{
	Node *node = new Node();
	node->data = sequence_char;
	node->eow = false;
	node->A = NULL;
	node->C = NULL;
	node->G = NULL;
	node->T = NULL;
	return node;
}



///******REMOVE******///
///Wrapper function for remove
// Function: remove
// Inputs: A string sequence
// Returns: Returns a string saying if a sequence was removed or not
// Does: This is a wrapper function that calls the real remove function
string Trie::remove(string sequence)
{
	Node *node;
	node = root;
	if (remove(node, sequence, i))
		return sequence + " removed";
	else
		return "No match found"; 
}


// Function: remove
// Inputs: a node pointer, the sequence to be removed and an integer i
// Returns: returns true or false depending on if the sequence got deleted
// Does: Removes a sequence from the trie if present. The i variable is used
// as a counter, determining how far along the string we've searched
bool Trie::remove(Node *node, string sequence, int i)
{
	if (i == int(sequence.size()) - 1) 
		return base_case(node);
	if (i == int(sequence.size()) and node->eow == false){
		bool result = false;
		return result;
	}
	int no_child = (int) node->eow + (int)(node->A != NULL) +  
	(int)(node->C != NULL) + (int)(node->G != NULL) + (int)(node->T != NULL);
	if (no_child == 0) 
		return false;

	bool result;
	if (node->A != NULL and  sequence[i] == 'A'){
		i++;
		result = remove(node->A, sequence, i); 
		if(result == true && no_child == 1 && i != 1)
			return delete_node(node);
	}
	if (node->C != NULL and sequence[i] == 'C') {
		i++;
		result = remove(node->C, sequence, i); 
		if(result == true && no_child == 1 && i != 1)
			return delete_node(node);
	}
	if (node->G != NULL and sequence[i] == 'G'){
		i++;
		result = remove(node->G, sequence, i);
		if(result == true && no_child == 1 && i != 1)
			return delete_node(node);
	}
	if (node->T != NULL and sequence[i] == 'T'){
		i++;
		result = remove(node->T, sequence, i);
		if(result == true && no_child == 1 && i != 1)
			return delete_node(node);
	}
	if (sequence[i] == '*'){
		post_order_delete(node);
		return true; 
	}

	return result; 
}

// Function: base_case
// Inputs: a node pointer
// Returns: returns a true or false value
// Does: Carries out the base case. returns true if node was deleted, 
// returns false if node was not deleted. 
bool Trie::base_case(Node *node)
{
	if (node->A == NULL and node->C == NULL and node->G == NULL and node->T == NULL)
		return true;
	if (node->eow == false)
		return false;

	return node_eow_change(node);
}

// Function: delete_node
// Inputs: a node pointer
// Returns: returns a true or false value
// Does: This function deletes a node and returns true once deleted 
bool Trie::delete_node(Node *node)
{
	if (node != NULL)
		delete node;
	return true;
}

// Function: node_eow_change
// Inputs: a node pointer
// Returns: returns a true or false value
// Does: This node changes the eow value of a node and
// returns false, because we don't delete a node
bool Trie::node_eow_change(Node *node)
{
	node->eow = false;
	remove_with_no_delete = true; 
	return remove_with_no_delete; 
}

////******QUERY******////
// Function: query
// Inputs: the sequence to be queried
// Returns: returns a string
// Does: Wrapper function for query that returns a notification
// of the percent similarity with a stored sequence
string Trie::query(string sequence)
{
	//A quick check, for if the first character matches
	bool check = in_tree(sequence[0], root);
	int size = int(sequence.size());
	seq = "";
	if (check == false)
		return "No match found";
	string postfix = "";
	string abc = "";
	double score = query_this(root, sequence, depth, match, complete, 
		size, postfix, abc);
	
	if (score == 0 or check == false)
		return "No match found";
	else
	{
		//Converts the score from double to string
		stringstream stream; 
		score = score * 100;
		stream << fixed << setprecision(2) << score;
		return "Match found " + abc + " " + stream.str();
	}
}

// Function: query_this
// Inputs: a node pointer, a sequence to be queried, 
// the depth of how far we have gone in the trie, the number of matches made
// and a boolean indicating if the match is complete
// Returns: returns a double for the score of the percent match
// Does: This function queries the whole tree, looking for the closest match 
// to the inserted sequence. 
double Trie::query_this(Node *node, string sequence, int depth, int match, 
	bool complete, int size, string postfix, string &abc)
{	
	double ratio, max_ratio = 0.0;
	if ((node->A == NULL and node->C == NULL and node->G == NULL 
		and node->T == NULL) or node->eow == true){
		
		if (depth > int(sequence.size()))
			ratio = double(match) / double(depth); 
		else 
			ratio = double(match) / double(size); 

		if (ratio > max_ratio) {
			seq = seq + postfix;
			max_ratio = ratio;
		}
		cout << max_ratio << endl;
		cout << match << " " << depth << " " << size << endl; 
		return max_ratio;
	}


	if (sequence == "" or node->eow == true or (sequence != "" 
		and node_finder(sequence[0], node) == NULL))
		complete = true;

	if (sequence == "" and node->eow == false)
	{
		int max_divisor;
		string postfixA = "", postfixC = "", postfixG = "", postfixT = "";
		string best = ""; 
		if (node->A != NULL){
			string node_char = "";
			postfixA =  shortest_sequence(node->A, node_char) ;
		}
		if (node->C != NULL){
			string node_char = "";
			postfixC = shortest_sequence(node->C, node_char);
		}
		if (node->G != NULL){
			string node_char = "";
			postfixG = shortest_sequence(node->G, node_char);
		}
		if (node->T != NULL){
			string node_char = "";
			postfixT = shortest_sequence(node->T, node_char);
		}
		
		//an array of all the lengths of our suffixes
		size_t list[4] = {postfixA.length(), postfixC.length(), 
			postfixG.length(), postfixT.length()};

		//finding the smallest suffix
		int smallest = numeric_limits<int>::max();
		int index; 
		for (int i = 0; i < 4; i++){
			if (list[i] < smallest and list[i] != 0){
				smallest = list[i];
				index = i;
			}
		}
		
		//breaking a tie with the smallest string and any other strings
		//that are the same size
		for (int i = 0; i < 4; i++){
			if (list[i] == smallest){
				if (best == "")
					best = index_string(i, '\0', postfixA, postfixC,
					 postfixG, postfixT);
				else 
					best = tie_breaker(best, i, '\0', postfixA, 
						postfixC, postfixG, postfixT, smallest);
			}
		}

		best = seq + best;
		abc = best; 

		//calculate then returns value
		if (size > best.size())
			max_divisor = size;
		else
			max_divisor = best.size();
		max_ratio = double(match) / double(max_divisor);
		complete = true;
		return max_ratio;

	}
    
	if (complete == false)
		return query_check(node, sequence, depth, match, complete, size,
		 postfix, abc);
	
	
	else if (complete == true){
		postfix = postfix + node->data;
		no_more_match(node, sequence, depth, match, complete, size, postfix, abc);
		return max_ratio;
	}
	return max_ratio;
}


// Function: shortest_sequence
// Inputs: A node pointer, a string to be concatenated
// Returns: returns the shortest sequence
// Does: This function calculates the shortest sequence
string Trie::shortest_sequence(Node *node, string node_char)
{
	string best = ""; 
	if (node == NULL)
		return node_char;
	if (node->eow == true){ 
		node_char = node_char + string(1, node->data); 
		return node_char;
	}
    
	string nodeA = shortest_sequence(node->A, node_char);
	string nodeC = shortest_sequence(node->C, node_char);
	string nodeG = shortest_sequence(node->G, node_char);
	string nodeT = shortest_sequence(node->T, node_char);
	
	size_t list[4] = {nodeA.length(), nodeC.length(), nodeG.length(), nodeT.length()};
	int smallest = numeric_limits<int>::max();
	int index; 
	for (int i = 0; i < 4; i++){
		if (list[i] < smallest and list[i] != 0){
			smallest = list[i];
			index = i;
		}
	}
	
	for (int i = 0; i < 4; i++){
		if (list[i] == smallest){
			if (best == "")
				best = index_string(i, node->data, nodeA, nodeC, nodeG, nodeT);
			else 
				best = tie_breaker(best, i, node->data, nodeA, nodeC, nodeG, 
					nodeT, smallest);
		}
	}
	return best;
    
}

// Function: tie_breaker
// Inputs: An integer index, a character to be passed to another function, 
// strings from all nodes
// Returns: returns the alphabetically ordered string
// Does: This function finds the alphabetically correct sequence
string Trie::tie_breaker(string best, int i, char node_data, string nodeA, 
	string nodeC, string nodeG, 
	string nodeT, int smallest)
{
	string competitor = index_string(i, node_data, nodeA, nodeC, nodeG, nodeT);
	string victor;
	for (int idx = 0; idx <= smallest; idx++)
	{
		if (best[idx] < competitor[idx])
			victor = best;
		else if (best[idx] == competitor[idx])
			continue;
		else
			victor = competitor; 
	}
	return victor;

}

// Function: index_string
// Inputs: An integer index, a character to be concatenated, strings from all
// nodes
// Returns: returns the concatenated string
// Does: This function concatenates the string from the shortest match
string Trie::index_string(int index, char node_data, string nodeA, string nodeC,
 string nodeG, string nodeT)
{
	if (index == 0)
	{
		if (node_data != '\0')
			return node_data + nodeA;
		else
			return nodeA;
	}
	else if (index == 1)
	{
		if (node_data != '\0')
			return node_data + nodeC;
		else 
			return nodeC;
	}
	else if (index == 2)
	{
		if (node_data != '\0')
			return node_data + nodeG;
		else 
			return nodeG;
	}
	else 
	{
		if (node_data != '\0')
			return node_data + nodeT;
		else 
			return nodeT;
	}
}

// Function: no_more_match
// Inputs: A node pointer, a string sequence, an integer depth, an integer match, 
// a boolean complete,
// and a string postfix
// Returns: returns max_ratio
// Does: This function recurses down the nodes that do not match the sequence
double Trie::no_more_match(Node *node, string sequence, int depth, 
	int match, bool complete, int size, string postfix, string &abc)
{
	if (node->A != NULL){
		depth++;
		max_ratio = query_this(node->A, sequence, depth, match, complete,
					size, postfix, abc);
	}
	else if (node->C != NULL){
		depth++;
		max_ratio = query_this(node->C, sequence, depth, match, complete, 
					size, postfix, abc);
	}
	else if (node->G != NULL){
		depth++;
		max_ratio = query_this(node->G, sequence, depth, match, complete, 
					size, postfix, abc);
	}
	else if (node->T != NULL){
		depth++;
		max_ratio = query_this(node->T, sequence, depth, match, complete, 
					size, postfix, abc);
	}
	return max_ratio;
}


// Function: query_check
// Inputs: A node pointer, a string sequence, an integer depth, an integer match, 
// a boolean complete,
// and a string postfix
// Returns: returns max_ratio
// Does: This function recurses down the question mark cases
double Trie::query_check(Node *node, string sequence, int depth, int match,
		 bool complete, int size, string postfix, string &abc)
{
	if (sequence[0] == '*'){
		if (node->A != NULL or node->C != NULL or
				node->G != NULL or node->T != NULL)
			return 1;
	}
	if (sequence[0] == '?'){
		if (node->A != NULL){
			queryA(node->T, sequence, depth, match, complete, size, postfix, abc);
			return max_ratio; 
		}
		if (node->C != NULL){
			queryC(node->T, sequence, depth, match, complete, size, postfix, abc);
			return max_ratio; 
		}
		if (node->G != NULL){
			queryG(node->T, sequence, depth, match, complete, size, postfix, abc);
			return max_ratio; 
		}
		if (node->T != NULL){
			queryT(node->T, sequence, depth, match, complete, size, postfix, abc);
			return max_ratio; 
		}		
	}
	if (sequence[0] == 'A' or sequence[0] == 'C' or sequence[0] == 'T' 
		or sequence[0] == 'G' ){
		query_normal(node, sequence, depth, match, complete, size, postfix, abc);
		return max_ratio;
	} 
}

// Function: query_normal
// Inputs: A node pointer, a string sequence, an integer depth, an integer match, 
// a boolean complete,
// and a string postfix
// Returns: does not return anything
// Does: This function recurses down the A node, in the case of a question mark. 
void Trie::query_normal(Node *node, string sequence, int depth, 
	int match, bool complete, int size, string postfix, string &abc)
{
	match++;
	depth++;
	seq = seq + sequence[0];
	char sq = sequence[0];
	sequence = sequence.substr(1, -1);
	max_ratio = query_this(node_finder(sq, node), sequence, depth, 
				match, complete, size, postfix, abc); 
	complete = true;
}

// Function: queryA
// Inputs: A node pointer, a string sequence, an integer depth, an integer 
// match, a boolean complete, and a string postfix
// Returns: does not return anything
// Does: This function recurses down the A node, in the case of a question mark. 
void Trie::queryA(Node *node, string sequence, int depth, int match,
 bool complete, int size, string postfix, string &abc)
{
	match++;
	depth++;
	sequence = sequence.substr(1, -1);
	query_this(node->A, sequence, depth, 
				match, complete, size, postfix, abc);
}

// Function: queryC
// Inputs: A node pointer, a string sequence, an integer depth, an integer match, 
// a boolean complete,
// and a string postfix
// Returns: does not return anything
// Does: This function recurses down the C node, in the case of a question mark. 
void Trie::queryC(Node *node, string sequence, int depth, int match, 
	bool complete, int size, string postfix, string &abc)
{
	match++;
	depth++;
	sequence = sequence.substr(1, -1);
	query_this(node->C, sequence, depth, 
				match, complete, size, postfix, abc);
}

// Function: queryG
// Inputs: A node pointer, a string sequence, an integer depth, an integer match, 
// a boolean complete,
// and a string postfix
// Returns: does not return anything
// Does: This function recurses down the G node, in the case of a question mark. 
void Trie::queryG(Node *node, string sequence, int depth, int match,
	 bool complete, int size, string postfix, string &abc)
{
	match++;
	depth++;
	sequence = sequence.substr(1, -1);
	query_this(node->G, sequence, depth, 
				match, complete, size, postfix, abc);
}

// Function: queryT
// Inputs: A node pointer, a string sequence, an integer depth, an integer match,
// a boolean complete,
// and a string postfix
// Returns: does not return anything
// Does: This frecurses down the T node, in the case of a question mark. 
void Trie::queryT(Node *node, string sequence, int depth, int match, 
	bool complete, int size, string postfix, string &abc)
{
	match++;
	depth++;
	sequence = sequence.substr(1, -1);
	query_this(node->T, sequence, depth, 
				match, complete, size, postfix, abc);
}


// Function: in_tree
// Inputs: a character and a node pointer
// Returns: Returns a boolean 
//Function to check if character is in tree.
bool Trie::in_tree(char a, Node *node)
{
	if (node->A != NULL and node->A->data == a)
		return true;
	else if(node->C != NULL and node->C->data == a)
		return true;
	else if(node->G != NULL and node->G->data == a)
		return true;
	else if(node->T != NULL and node->T->data == a)
		return true;
	return false; 
}		


// Function: node_finder
// Inputs: sequence character and node pointer
// Returns: Returns a node pointer to the desired node
// Does: This function finds the appropriate node child we want to move
// to, this is important because each node has four diffefent pointers
// we need to specify which node we want to move to when we traverse 
// down the trie.  
Node *&Trie::node_finder(char alph, Node *node)
{
	if (alph == 'A')
		return node->A;
	else if (alph == 'C')
		return node->C;
	else if (alph == 'G')
		return node->G;
	else if (alph == 'T')
		return node->T;
	
}


// Function: EOW_marker
// Inputs: A node pointer and the length of the sequence
// Returns: Does not return anything
// Does: This Function changes the end of word marker for a character, 
// if it needs to be changed; we ensure this, by checking the length of
// the sequence. 
void Trie::EOW_marker(Node *node, int seq_length)
{
	if (seq_length == 0)
		node->eow = true;
}


// Function: manager
// Inputs: No inputs
// Returns: Does not return anything
// Does: This function manages the requests given to the trie, 
// it then returns to an output file. 
void Trie::manager(char a, string sequence, ofstream &outfile)
{
    if (a == 'i')
        insert_sequence(sequence);
    else if (a == 'r')
        outfile << remove(sequence) << endl;
    else if (a == 'q')
        outfile << query(sequence) << endl;  
}

// Function: post_order_print
// Inputs: No inputs
// Returns: Does not return anything
// Does: Wrapper function that calls the post order print function
void Trie::post_order_print() const
{
	return post_order_print(root);
}

// Function: post_order_print
// Inputs: No inputs
// Returns: Does not return anything
// Does Prints the contents of the trie in post order fashion
void Trie::post_order_print(Node *node) const
{
	if (node == NULL)
		return;

	post_order_print(node->A);
	post_order_print(node->C);
	post_order_print(node->G);
	post_order_print(node->T);
	cout << node->data << endl;
}



// Function: print
// Inputs: No inputs
// Returns: Does not return anything
// Does: Calls the print function
void Trie::print() const
{
	string seq = " ";
	return print(root, seq);
}

// Function: print
// Inputs: No inputs
// Returns: Does not return anything
// Does: Prints the contents of the trie in sequence fashion
void Trie::print(Node *node, string seq) const
{
	if (node->A != NULL){
		if (node->A->eow == true){
			cout << seq + node->A->data;
		}
		print(node->A, seq + node->A->data);
		cout << " ";
	}

	if (node->C != NULL){
		if (node->C->eow == true){
			cout << seq + node->C->data;
		}
		print(node->C, seq + node->C->data);
		cout << " ";
	}
	if (node->G != NULL){
		if (node->G->eow == true){
			cout << seq + node->G->data;
		}
		print(node->G, seq + node->G->data);
		cout << " "; 
	}
	if (node->T != NULL){
		if (node->T->eow == true)
			cout << seq + node->T->data;
		print(node->T, seq + node->T->data);
		cout << " ";
	}
}