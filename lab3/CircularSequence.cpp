/*
 *      CircularSequence.cpp 
 *      PartyPlaylist 
 *      Comp 15 Lab 3
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Documentation added by Mark A. Sheldon, Tufts University
 */

#include <iostream>
#include <stdexcept>

#include "CircularSequence.h"


using namespace std;


/*
 * Return the index of the next element in the sequence.
 * Wraps around!
 */
int CircularSequence::nextIndex(int index)
{

	int temp = (index + 1) % capacity; 
	return temp;

}


/* Default Constructor */
CircularSequence::CircularSequence()
{
    init(INIT_CAPACITY);
}

/* 
 * Overloaded Constructor for a sequence with a hint for an initial
 * capacity. 
 */
CircularSequence::CircularSequence(int initialCapacity)
{
    init(initialCapacity);
}

/*
 * Initialize a new, empty sequence with an initial capacity.
 */
void CircularSequence::init(int initialCapacity)
{
    capacity      = initialCapacity;
    sequenceArray = new ElementType[capacity];
    currentSize   = 0;
    front         = 0;
    back          = 0;
}

/*
 * Destructor:  recycles the dynamically allocated array containing
 * the data.
 */
CircularSequence::~CircularSequence()
{
	delete [] sequenceArray;
}

/* 
 *  Add given element to the back of the list (at element
 *  currentSize). 
 *  Return true if element is successfully added.
 */
bool CircularSequence::addAtBack(ElementType elem) 
{
    if (currentSize == capacity) 
    {
        expand();
    }
    sequenceArray[back] = elem;
    back = nextIndex(back);
    currentSize++;

    return true;
}

/* 
 *  Add given element to the front of the list (at element 0)
 *  Return true if element is successfully added.
 */
bool CircularSequence::addAtFront(ElementType elem)
{
       
    sequenceArray[(front - 1) % capacity] = elem;
    currentSize++;
        
    return true; 
}
                
/*
 * Remove the element at the back of the list (index currentSize - 1)
 * and return it.
 */
ElementType CircularSequence::removeFromBack() 
{
	back = currentSize - 1;
	int temp = currentSize;
    currentSize--; 
    return sequenceArray[temp];
}
 
/*
 * Remove the element at the front of the list (element 0)
 * and return it.
 */
ElementType CircularSequence::removeFromFront()
{
	int temp = front;
    front = (front + 1) % capacity;
    currentSize--;
    return sequenceArray[temp];

}

/*
 * Expand the capacity of the array by a factor of 2.
 */
void CircularSequence::expand() 
{
    ElementType *biggerArray = new ElementType[capacity * 2];
    int index = front;

	for (int i = 0; i < capacity; i++)
	{
	    biggerArray[i] = sequenceArray[index];
	    index = nextIndex(index);
	}
	
	front = 0;
    capacity = capacity * 2;
    back = currentSize;

	delete []sequenceArray;
    sequenceArray = biggerArray;
}

/*
 * Print the contents of the sequence, one element per line.
 */
void CircularSequence::printSequence() 
{
    int currIndex = front;
    for (int i = 0; i < currentSize; i++) 
    {
        cout << sequenceArray[currIndex] << endl;
        currIndex = nextIndex(currIndex);
    }
}
