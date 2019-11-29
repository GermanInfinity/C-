/*
 * GrocerySim.cpp
 * COMP15 HW3
 * Fall 2018
 * Akwarandu Ugo Nwachuku
 * Implementation of testCheckoutQueue.cpp
 * This class implements a check on the functions of the checkoutqueue
 * class. It also has in comments a test on the grocerysim class aswell. 
 */

#include "CheckoutQueue.h"
#include "GrocerySim.h"
#include <iostream>
#include <fstream>
#include "shopper.h"
using namespace std;

const string SHOPPER_LIST = "list.txt";

/*
int main() 
{ 
	string filename;
    ifstream inputFile;
    inputFile.open(SHOPPER_LIST.c_str());
    string info = "";

    GrocerySim store(3, 1, 5);

    store.run(inputFile);
    
    //cout << "Hey";
    //store.create_queues();
    
    //GrocerySim store(3, 1, 5);
    return 0;

}
*/

 //CheckoutQueue test.
int main() 
{

	CheckoutQueue queue_1;
	Shopper jeff; 
	Shopper jane;
	Shopper john;

	//Shopper initialization: Jeff
	jeff.id = 6;
	jeff.arrival_time = 6;
	jeff.num_items = 6;
	jeff.items_left = 6;

	//Shopper initialization: Jane
	jane.id = 6;
	jane.arrival_time = 6;
	jane.num_items = 6;
	jane.items_left = 6;

	//Shopper initialization: John
	john.id = 6;
	john.arrival_time = 6;
	john.num_items = 6;
	john.items_left = 6;


	//Enqueue test.
	//This test adds a shopper the three shoppers to the queue. 
	queue_1.enqueue(jeff);

	queue_1.enqueue(jane);

	queue_1.enqueue(john);
	queue_1.print();

	cout << "Current size: " << queue_1.size() << endl;
	//Total items function test
	//This test returns the total amount of items.
    cout << "Total items: " << queue_1.totalItems() << endl;

    //Dequeue function test
    //This function removes an element from the front. 
    queue_1.dequeue(); 

    //Front function test
    //Checks the new front element
    //print << "Front: " << queue_1.front() << endl;
    cout << queue_1.front().id;
    //queue_1.print();


	
	return 0;

}
