/*
 * CheckoutQueue.h
 * COMP15
 * Fall 2018
 * Akwarandu Ugo Nwachuku
 * This is the implementation of the declaration of all the 
 * private functions and public variables I used in the .cpp file. 
 *
 */

#ifndef GROCERYSIM_H
#define GROCERYSIM_H
#include <istream>
#include <string>
#include <cstdio>
#include "shopper.h"
#include "CheckoutQueue.h"

using namespace std;

class GrocerySim
{
public:
	GrocerySim();
	GrocerySim(int num_standard_queue, int num_express, int max_express);
	~GrocerySim();
	void run (istream &infile);
    
	void create_queues();
    

private:
	int num_standard_queue;
	int num_express_lane;
	int maxim_express;
	int timer;
	int entry_no;
	CheckoutQueue *lanes;
	int shortest_queue(bool);

	

};

#endif