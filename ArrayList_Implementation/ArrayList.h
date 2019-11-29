/*
 * ArrayList.h
 * COMP15
 * Fall 2018 
 *
 * This file is the header file of the ArrayList class. 
 * It declares all the variables used in the ArrayList class.
 */

#include "Pirate.h"

#ifndef ARRAY_H_
#define ARRAY_H_

const int MAX_PIRATES = 100;

class ArrayList
{
public:
    // Default constructor
    ArrayList();
    //Destructor
    ~ArrayList();

    // The basic operations:
    // Insert, Delete, and Find
    Pirate find_pirate(Pirate, bool &) const;
    void insert_pirate(Pirate);
    void delete_pirate(Pirate);
    Pirate get_next_pirate();

    // Start over at the beginning of the list
    void make_empty();
    void reset_array();

    // Return some basic info
    bool is_full() const;
    int get_length() const;

    // Print the array
    void print(ostream &) const;
    // Extend the array
    void extend();
    // Shrink the array
    void shrink();

private:
    int length;
    int curr_pos;
    Pirate *pirates;
    int capacity;
};

#endif
