/*
 * LinkedList.cpp
 * COMP15
 * Fall 2018
 * 
 * Implementation for Linked List of Green Line Extension Stations
 */

#include "LinkedList.h"
#include <iostream>
using namespace std;

// Default constructor
LinkedList::LinkedList()
{
    length = 0;
    head = NULL;
    curr_pos = NULL;
}

// Destructor
LinkedList::~LinkedList() 
{
    make_empty();
}

// Assignment operator
LinkedList & LinkedList::operator = (const LinkedList &l)
{
    NodeType *temp = NULL;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
    length = l.length;
    curr_pos = NULL;
    if (l.head == NULL)
        head = NULL;
    else
    {
        head = new NodeType;
        head->info = l.head->info;
        head->next = NULL;
        NodeType *curr = head;
        NodeType *orig = l.head;
        while (orig->next != NULL)
        {
            curr->next = new NodeType;
            curr->next->info = orig->next->info;
            curr->next->next = NULL;
            orig = orig->next;
            curr = curr->next;
        }
    }
    return *this;
}

// Function: get_length
// Input: nothing
// Returns: the length
// Does: returns the length of the LL
int LinkedList::get_length() const
{
    return length;
}

// Function: insert_station
// Input: a Station object
// Returns: Does not return anything
// Does: Adds a Station object to the head of the list. 
void LinkedList::insert_station(Station s)
{
    if (head == NULL)
    {
        head = new NodeType;
        head->info = s;
        curr_pos = head;
        head->next = NULL;
        length++;
    }
    else
    {
        NodeType *temp = new NodeType;
        temp->info = s;
        temp->next = head;
        head = temp;
        length++;
    }
    
}

// Function: remove_station
// Input: a Station object
// Returns: Does not return anything
// Does: Removes an identical station in the linked list, 
// if it's info is equal to a station in the list. 
void LinkedList::remove_station(Station s)
{
    NodeType *temp = NULL; 
    temp = head;
    if (head == NULL)
    {
        return;
    }
    while (temp != NULL)
    {   
        if (temp->info.is_equal(s))
        {
            head = head->next;
            delete temp;
            length--;
        }
        if (temp->next != NULL)
        {
            if (temp->next->info.is_equal(s))
            {
                temp->next = temp->next->next;
                delete temp->next;
                length--;
            }
        }
        
        temp = temp->next;
    }
}


// Function: get_next_station
// Input: No inputs
// Returns: A different station from the list
// Does: Each time this function is called upon, it returns a station from the
// list starting at head. 
Station LinkedList::get_next_station()
{
    NodeType *temp = NULL; 

    /*if (curr_pos == NULL)
    {
        curr_pos = head;
        temp = curr_pos;
        curr_pos->next = head->next;
        return temp->info;
    }*/
    
    if (curr_pos->next != NULL)
    {
        temp = curr_pos;
        curr_pos = curr_pos->next;
        return temp->info;
    }

    else 
    {
        temp = curr_pos;
        curr_pos = head; 
        return temp->info;
    }
    
}

// Function: reset_curr_pos
// Input: None
// Returns: None
// Does: Resets curr_pos variable
void LinkedList::reset_curr_pos()
{
   curr_pos = NULL;
}


// Function: make_empty()
// Input: no inputs
// Returns: does not return anything, but has a return statement for a base 
// condition
// Does: iterates through and deletes all the elements in the linked list
void LinkedList::make_empty()
{
    while (head != NULL)
    {
        NodeType *temp = NULL;
        temp = head;
        head = temp->next;
        delete temp;
    }
    
}


// Function:print
// Input: takes in an ostream object
// Returns: does not necessarily return anything, but prints to a file
// Does: prints the name of as station and it's distance from another 
// station to a file
void LinkedList::print(ostream &out)
{
    NodeType *temp = NULL;
    temp = head;
    int count = get_length();
    while (temp != NULL)
    {
        temp->info.print(out);
        if ((count - 1) == 0)
        { 
            out << " " << count - 1 << endl;
        }
        else 
        {
            out << " " << count - 1 << " == ";
        }
        count--;
        temp = temp->next;
    }

}



