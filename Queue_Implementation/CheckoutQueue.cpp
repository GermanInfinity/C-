/*
 * CheckoutQueue.cpp
 * COMP15 HW3
 * Fall 2018
 * Akwarandu Ugo Nwachuku
 * Implementation of the CheckoutQueue class
 * This is my implementation of a queue for this assignment. 
 * I used a circular list data structure to implement the queue. The
 * class is capable of adding members to the queue and dequeueing 
 * members aswell. It is also able to sum the totalitems on a certain queue.
 */

#include <iostream>
#include "CheckoutQueue.h"

using namespace std;

// Function: CheckoutQueue
// Input: No input
// Returns: Does not return anything 
// Does: Initializes an empty queue and length of queue parameter 
CheckoutQueue::CheckoutQueue()
{
	capacity = 10;
	queue = new Shopper[capacity];
	current_size = 0;
	top = 0;
	back = 0;
}

// Function: ~CheckoutQueue
// Input: No input
// Returns: Does not return anything
// Does: Delete the whole structure of the queue and liberates space
CheckoutQueue::~CheckoutQueue()
{
	delete [] queue;

}

// Function: isEmpty()
// Input: No input
// Returns: Returns true or false
// Does: This function returns true if the size of the list is 0, and false
// if otherwise 
bool CheckoutQueue::isEmpty()
{
	if (current_size == 0)
	{
		return true;
	}
	return false;	
}

// Function: size()
// Input: No input
// Returns: Returns the size of the queue
// Does: This function returns the number of shoppers in the queue
int CheckoutQueue::size()
{
	return current_size;
}


// Function: totalItems
// Input: No input
// Returns: Returns an int value of the totalitems in a queue
// Does: Computes the sum of all the items held by each shopper in a queue
int CheckoutQueue::totalItems()
{
	int totalItems = 0;
	int i = top;
	int count = 0;
	while(count < current_size) 
	{
		totalItems += queue[i].num_items;
		i = nextSpot(top);
		count++;
	}
	return totalItems;
}


// Function: enqueue
// Input: A shopper
// Returns: Does not return anything
// Does: Adds a shopper to the end of a queue
void CheckoutQueue::enqueue(Shopper toAdd)	
{
	if (current_size == capacity) 
	{
		expand();
	}
	queue[back] = toAdd;
	back = nextSpot(back);
	current_size++;
}

// Function: front
// Input: No input
// Returns: Reference to front element
// Does: This function returns the first shopper in the queue, if the
// queue is not empty.
Shopper &CheckoutQueue::front()
{
	if (current_size == 0) //queue.isempty(), not working?
	{
		cerr << "empty_queue" << endl;
	}
	return queue[top];
}

// Function: dequeue
// Input: 
// Returns: Does not return anything.
// Does: This function removes an element from the front of the queue,
// if the queue is not empty.
void CheckoutQueue::dequeue()
{
	if (current_size == 0)
	{
		cerr << "empty_queue" << endl;
	}
	top = nextSpot(top);
	current_size--;
}



//Insert any private functions in here

// Function: nextSpot
// Input: Takes in index as an input 
// Returns: Returns an int value of the next available position
// Does: Finds the next index position of open space in the list,
// it is capable of looping around the list to find the next spot
int CheckoutQueue::nextSpot(int index)
{
	int next_spot = 0;
	next_spot = (index + 1) % capacity;
	return next_spot;
}


// Function: expand
// Input: Does not have an input 
// Returns: Does not return anything
// Does: Doubles the capacity of the queue
void CheckoutQueue::expand() 
{
    Shopper *biggerQueue = new Shopper[capacity * 2];
    int index = top;

	for (int i = 0; i < capacity; i++)
	{
	    biggerQueue[i] = queue[index];
	    index = nextSpot(index);
	}
	
	top = 0;
    capacity = capacity * 2;
    back = current_size;

	delete []queue;
    queue = biggerQueue;
}



// Function: print
// Input: Does not have an input 
// Returns: Does not return anything
// Does: prints out the queue
void CheckoutQueue::print() 
{

    cout << "Current Size: " << current_size << endl;
    cout << "Top: " << top << endl;
    cout << "Back: " << back << endl;


}


