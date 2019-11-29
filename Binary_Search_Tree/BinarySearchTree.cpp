/*
 * BinarySearchTree.cpp
 * Akwarandu Ugo Nwachuku
 * 17/October/2018
 * COMP 15 HW4
 * This is essentially the interface for the BinaryTree class. It uses a 
 * a pointer to a node struct in memory. And each node struct in memory 
 * has a left and right pointer, representing the children of a node. 
 */

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>
#include <string>

#include "BinarySearchTree.h"

using namespace std;

//Default constructor
BinarySearchTree::BinarySearchTree()
{
    root = NULL;
}

BinarySearchTree::~BinarySearchTree()
{
    post_order_delete(root);
    root = NULL;  
}

//Function: post_order_delete
//Input: A pointer to a node
//Returns: Does not return anything
//Does: post_order_delete, deletes the nodes starting at the left child 
//to the right child then the node. 
void BinarySearchTree::post_order_delete(Node *node)
{
    if (node == NULL)
        return;
    post_order_delete(node->left);
    post_order_delete(node->right);
    delete node;
    
}

//copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
        // use pre-order traversal to copy the tree
    root = pre_order_copy(source.root);
}

//Function: operator= (Assignment overload)
//Input: A reference ot a binary tree in memory 
//Returns: A binary tree
//Does: Overloads the 'equals to' operator to enable it copy an already 
//initialized tree to an old tree. It does a deep copy because it uses 
//the function pre_order_copy. 
BinarySearchTree &BinarySearchTree::operator= (const BinarySearchTree &source)
{
    if (this == &source)
    {
        return *this;
    }
    else if(this != &source)
    {
        post_order_delete(this->root);
        this->root = pre_order_copy(source.root);
    }
    return *this;
}

//Function: pre_order_copy
//Input: A pointer to a node
//Returns: A pointer to a node
//Does: This function traverse the tree in a pre_order format. It does
//a deep copy of all the nodea, by creating a new node and copying over the 
//details of the node to be copied to the new node. 
Node *BinarySearchTree::pre_order_copy(Node *node) const
{
    if (node == NULL)
        return NULL;
    Node *new_node = new Node();
    new_node->data = node->data;
    new_node->count = node->count;
    new_node->left = pre_order_copy(node->left);
    new_node->right = pre_order_copy(node->right);
    return new_node;
}

int BinarySearchTree::find_min() const
{
    if (root == NULL)
        return INT_MIN;
    return find_min(root)->data;
}

//Function: find_min(Node *node)
//Input: A pointer to a node
//Returns: A pointer to a node
//Does: Searches for and returns a node pointer to the minimum value in a tree
Node *BinarySearchTree::find_min(Node *node) const
{
    Node *min_node;
    if (node->left != NULL)
    {
        min_node = find_min(node->left);
    }
    else
        min_node = node;
    
    return min_node;
}

int BinarySearchTree::find_max() const
{
    if (root == NULL)
        return INT_MAX;
    return find_max(root)->data;
}

//Function: find_max(Node *node)
//Input: A pointer to a node
//Returns: A pointer to a node
//Does: Searches for and returns a node pointer to the maximum value in a tree
Node *BinarySearchTree::find_max(Node *node) const
{
    Node *max_node;
    if (node->right != NULL)
    {
        max_node = find_max(node->right);
    }
    else 
    {
        max_node = node;
    }
    return max_node;
}

bool BinarySearchTree::contains(int value) const
{
    if (root->data == value)
        return true;
    return contains(root, value);
}

//Function: contains
//Input: A pointer to a node and an int 
//Returns: A true or false value
//Does: Checks the tree for an integer value contained in the tree. 
bool BinarySearchTree::contains(Node *node, int value) const
{
    if (node == NULL)
        return false;

    else if (value < node->data)
    {
        contains(node->left, value);
    }
    else if (value > node->data)
    {
        contains(node->right, value);
    }

    return true;
}

void BinarySearchTree::insert(int value)
{
	insert(root, NULL, value);
}

//Function: insert
//Input: a pointer to a node, a pointer the parent, an integer value
//Returns: Does not return anything
//Does: This function is responsible for inserting a node to the appropriate
//location in a tree, right or left, depending on it's value. 
void BinarySearchTree::insert(Node *root, Node *parent, int value)
{
    if (this->root == NULL){
        insert_base(value);
        return;
    }
    else if (value > root->data and root != NULL){
        Node *node; 
    	parent = root;
    	node = parent->right;
    	if (node == NULL) {
            string side = "right";
            insert_now(value, parent, side);
    	}
        else
    	   insert(node, parent, value);
    }
    else if (value < root->data and root != NULL){
        Node *node;
    	parent = root;
    	node = parent->left;
    	if (node == NULL){
            string side = "left";
            insert_now(value, parent, side);
    	}
    	else
           insert(node, parent, value);
    }
    else if (value == root->data)
        root->count++; 
}


//Function: insert_base
//Input: value
//Returns: Does not return anything
//Does: This function inserts a root base to the tree, with the value passed 
//in.
void BinarySearchTree::insert_base(int value)
{
    Node *node = new Node; 
    node->right = NULL;
    node->left = NULL;
    this->root = node;
    node->data = value;
    node->count = 1;
}


//Function: insert_now
//Input: An integer value, a pointer to the parent in the tree, and a string
//of what side to place the node
//Returns: Does not return anything
//Does: This function inserts a node to either the right or left of a node. 
//The side is determined by the arguement "side".
Node *BinarySearchTree::insert_now(int value, Node *parent, string side) 
{
    if (side == "left")
    {
        Node *new_node = new Node; 
        parent->left = new_node;
        new_node->data = value;
        new_node->count = 1;
        new_node->right = NULL; 
        new_node->left = NULL;
        return new_node;
    }
    
    else if (side == "right")
    {
        Node *new_node = new Node; 
        parent->right = new_node;
        new_node->data = value;
        new_node->count = 1;
        new_node->right = NULL; 
        new_node->left = NULL;
        return new_node;
    }
}

bool BinarySearchTree::remove(int value)
{
    return remove(root, NULL, value);
}


//Function: remove
//Input: An pointer to a node, a pointer to a parent and an integer value 
//to be removed. 
//Returns: Returns a true or false value. 
//Does: This function removes the int value passed into the function. 
//It first checks if the value is contained within the tree, then it handles
//a removal of a node for the case where the node is a leaf, the node 
//has one child, and the node has two children. It also considers if the tree 
//was empty or not. 
bool BinarySearchTree::remove(Node *node, Node *parent, int value)
{
    if (node == NULL) //empty tree
        return false;
    if (contains(value)) {
        if (value < node->data){
            parent = node;
            remove(node->left, parent, value);
        }
        else if (value > node->data){
            parent = node;
            remove(node->right, parent, value);
        }
        else if (value == node->data){
            //leaf remove
            if (parent->right == node and node->right == NULL and node->left == NULL){
                delete node;
                parent->right = NULL;
                return true; 
            }
            else if (parent->left == node and node->left == NULL and node->right == NULL){
                delete node;
                parent->left = NULL;
                return true;
            }
            //1 child
            if (node->left == NULL)
                one_child_remove(node, parent, true);
            else if (node->right == NULL)
                one_child_remove(node, parent, false);

            //2 child: Replace node with max_left_bst.
            if (node->left != NULL and node->right != NULL){
                two_child_remove(node);
            }    
        } 
    }
    return false; 
}


//Function: one_child_remove
//Input: An pointer to a node
//Returns: Returns true
//Does: This function removes a node with one child. It always 
//returns true because it is only called in the case this node is present
bool BinarySearchTree::one_child_remove(Node *node, Node *parent, bool check)
{
    if (check == true){
        if (parent->left == node){
            parent->left = node->right;
            delete node;
            return true;
        }
        else if (parent->right == node){
            parent->right = node->right;
            delete node;
            return true;
        }
    }
    else {
        if (parent->left == node){
            parent->left = node->left;
            delete node;
            return true;
        }
        else if (parent->right == node){
            parent->right = node->left;
            delete node;
            return true;
        }
    }
}


//Function: two_child_remove
//Input: An pointer to a node
//Returns: Returns true
//Does: This function removes a node with two children. It always 
//returns true because it is only called in the case this node is present
bool BinarySearchTree::two_child_remove(Node *node)
{
    Node *temp_parent, *temp;
    temp = find_max(node->left);
    temp_parent = find_parent(root, temp);

    int temp_v = temp->data;
    int count = temp->count;

    remove(temp, temp_parent, temp->data);

    node->data = temp_v;
    node->count = count;
    return true;
}

int BinarySearchTree::tree_height() const
{
    return tree_height(root);
}

//Function: tree_height
//Input: An pointer to a node
//Returns: Returns an integer value
//Does: This function recursively counts the height of the tree
int BinarySearchTree::tree_height(Node *node) const
{
    if (node == NULL)
    {
        return -1;
    }
    return (max(tree_height(node->left), tree_height(node->right) + 1));
    
}

// returns the total number of nodes
int BinarySearchTree::node_count() const
{
    return node_count(root);
}

//Function: node_count
//Input: An pointer to a node
//Returns: Returns an integer value
//Does: This function recursively counts the number of nodes in the tree
int BinarySearchTree::node_count(Node *node) const
{
    if (node == NULL)
    {
        return 0;
    }

    return node_count(node->left) + node_count(node->right) + 1;
}

// return the sum of all the node values (including duplicates)
int BinarySearchTree::count_total() const
{
    return count_total(root);
}

//Function: count_total
//Input: An pointer to a node
//Returns: Returns an integer value
//Does: This function recursively counts the total number of nodes in the 
//tree
int BinarySearchTree::count_total(Node *node) const
{
    if (node == NULL)
    {
        return 0;
    }

    return count_total(node->left) + count_total(node->right) + 
           (node->data * node->count); 

}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() const
{
    printPretty(root, 1, 0, std::cout);
}

Node *BinarySearchTree::find_parent(Node *node, Node *child) const
{
    if (node == NULL) return NULL;

        // if either the left or right is equal to the child,
        // we have found the parent
    if (node->left == child or node->right == child) 
    {
        return node;
    }

        // Use the binary search tree invariant to walk the tree
    if (child->data > node->data) 
    {
        return find_parent(node->right, child);
    } 
    else 
    {
        return find_parent(node->left, child);
    }
}
