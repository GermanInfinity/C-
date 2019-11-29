/*
 * GrocerySim.cpp
 * COMP15 HW3
 * Fall 2018
 * Akwarandu Ugo Nwachuku
 * Implementation of the GrocerySim class
 * This is my implementation of the simulation of the grocery store. 
 * I used a dynamic array to hold my queue objects. 
 * The simulation runs and outputs the amount of time a shopper spent
 * at the checkoutqueue and how many items the shopper left with. 
 * The program also takes in how many checkout queues to assign.
 */


#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include "GrocerySim.h"
#include "CheckoutQueue.h"
#include "shopper.h"


using namespace std;

GrocerySim::GrocerySim()
{
	num_standard_queue = 0;
	num_express_lane = 0;
	maxim_express = 0;
    timer = 0;
    entry_no = 0;
    lanes = new CheckoutQueue[1];
}

// Function: GrocerySim
// Input: The number of standard checkout lanes, number of express checkout
// lanes, and the greatest number of items a shopper can have to use the
// express lane
// Returns: Does not return anything
// Does: This function sets the private constructors of the class
GrocerySim::GrocerySim(int num_std, int num_express, int max_express)
{
	num_standard_queue = num_std;
	num_express_lane = num_express;
	maxim_express = max_express;
    timer = 0;
    entry_no = 0;
    lanes = new CheckoutQueue[num_standard_queue + num_express_lane];
}

// Function: ~GrocerySim
// Input: No inputs
// Returns: Does not return anything
// Does: Destroys the dynamic list of queues
GrocerySim::~GrocerySim()
{
	delete [] lanes;
}

// Function: run
// Input: Takes in an input file
// Returns: 
// Does: 

void GrocerySim::run(istream &infile)
{	
    int a, b;
    infile >> a;
    infile >> b;

    while (timer < 400)
    {
        for(int i = 0; i < (num_standard_queue + num_express_lane); i++) // each lane
        {
            if ((lanes[i]).isEmpty() == false) // lane not empty
            {
                //cout << "Lane " << i << " is not empty at time: " << timer << endl;
                (lanes[i]).front().items_left--;
                if ((lanes[i]).front().items_left == 0)
                {
                    cout << "Shopper " << (lanes[i]).front().id << " arrived at " <<  (lanes[i]).front().arrival_time <<
                    " with " << (lanes[i]).front().num_items << " items, " << "took " << timer - (lanes[i]).front().arrival_time << " units."<< endl;
                    (lanes[i]).dequeue(); //increase time? 
                }
            }
        }
        if (a == timer)
        {
            Shopper person;
            entry_no++;

            person.id = entry_no;
            person.arrival_time = a;
            person.num_items = b;
            person.items_left = b;
            if (b <= maxim_express)
            {
                lanes[shortest_queue(false)].enqueue(person); //Express queue
            }
            else
            {
                lanes[shortest_queue(true)].enqueue(person); //Standard queue
            }
            infile >> a;
            infile >> b;
        }
        timer++;
    }
}
      

// Function: shortest_queue
// Input: Takes in a true or false value
// Returns: Returns the index of the shortest queue
// Does: It takes in a value that tells it if we are looking for the 
// shortest queue in the standard lane or express lane. It then computes
// the index of the shortest queue in our list of queues 

int GrocerySim::shortest_queue(bool check)
{ 
    int min;
    if (check)
    {
        min = 0;
        for (int i = 0; i < num_standard_queue; i++)
        {
            if (lanes[i].totalItems() <= lanes[min].totalItems())
            {
                min = i;
            }
        }
        return min;
    }

    //Express
    else
    {
        min = num_standard_queue;
        for (int i = num_standard_queue; i < num_express_lane; i++)
        {  
            if (lanes[i].totalItems() <= lanes[min].totalItems())
            {
                min = i;
            }
        }
        return min;
    }
}
