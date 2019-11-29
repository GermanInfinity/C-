/*
 * CheckoutQueue.h
 * COMP15
 * Fall 2018
 * Akwarandu Ugo Nwachuku
 * This is the implementation of the declaration of all the 
 * private functions and public variables I used in the .cpp file. 
 *
 */

#ifndef CHECKOUTQUEUE_H
#define CHECKOUTQUEUE_H

#include "shopper.h"

class CheckoutQueue
{
public:
	CheckoutQueue();
	~CheckoutQueue();
	bool isEmpty();
	int size();
	int totalItems();
	void enqueue(Shopper);
	Shopper &front();
	void dequeue();
	void print();
private:
	
	int capacity;
	int current_size;
	int top;
	int back;
	Shopper *queue;

    //Private functions.
	int nextSpot(int index); 
	void expand();

	
	
};

#endif