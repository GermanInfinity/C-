/*
 * Array.cpp
 * Akwarandu Ugo Nwachuku
 * 17th September, 2018
 * COMP 15 HW1
 *
 *
 * This implementation addresses the ArrayList class. The class is 
 * responsible for organizing the list the pirate names gets stored in. 
 * It does this with it's helper functions, that are capable of shrinking and
 * extending the list, depending on how much space is available in the list. 
 */

#include "ArrayList.h"
#include <iostream>

// Default constructor
// The default constructor does not accept any parameters, but instead
// creates variables that would be required everywhere through out the code. 
// 'capacity' is a new variable added to keep track of the list of pirates. 
ArrayList::ArrayList()
{
    length = 0;
    curr_pos = 0;
    pirates = new Pirate[MAX_PIRATES];
    capacity = MAX_PIRATES;
}

//Destructor
ArrayList::~ArrayList()
{
    delete []pirates;
}

// Function find_pirate
// Inputs: Pirate object, bool by reference
// Returns: Pirate object
// Does: Looks for pirate in the array, modifies bool if found
//       Returns the object from the list and not the passed one
//       (In case they're different.)
Pirate ArrayList::find_pirate(Pirate p, bool &found) const
{
    int location = 0;

    while ((location < length) && !found)
    {
        if (p == pirates[location])
        {
            found = true;
            p = pirates[location];
            break;
        }
        location++;
    }
    return p;
}

// Function insert_pirate
// Inputs: Pirate object
// Returns: Nothing
// Does: Adds Pirate to end of array, increases length
void ArrayList::insert_pirate(Pirate p)
{
    bool found = false;
    find_pirate(p, found);
    if (found)
    {
        return;
    }
    else
    {   
        if (get_length() >= capacity)
            {
                extend();
            }
        pirates[length] = p;
        length++;
    }
}

// Function delete_pirate
// Inputs: Pirate object
// Returns: Nothing
// Does: Deletes pirate, shifts everything else over
void ArrayList::delete_pirate(Pirate p)
{
    for (int i = 0; i < length; i++)
    {
        if (p == pirates[i])
        {
            for (int idx = i; i < length; i++)
            {
                pirates[idx] = pirates[idx + 1];
                if (idx == length-1)
                {
                    break;
                }
            }
            length--;
            if (get_length() < capacity / 2)
            {
                shrink();
            }
        }
    }
}





// Function get_next_pirate
// Input: None
// Returns: Pirate object
// Does: Returns pirate at curr_pos
//       Increments curr_pos, but wraps around
Pirate ArrayList::get_next_pirate()
{
    Pirate p = pirates[curr_pos];
    curr_pos = (curr_pos + 1) % length;
    return p;
}

// Function make_empty
// Input: none
// Returns: none
// Does: sets length to 0 (memory not modified)
void ArrayList::make_empty()
{
    length = 0;
}









// Function reset_array
// Input: none
// Returns: none
// Does: sets curr_pos to 0 
void ArrayList::reset_array()
{
    curr_pos = 0;
}








// Function print
// Input: none, const
// Returns: none
// Does: Prints array from 0 to length
void ArrayList::print(ostream &outfile) const 
{
    for (int i = 0; i < length; i++)
    {    
        if (i == length - 1)
        {
            pirates[i].print(outfile);
            break;
        }
        
        pirates[i].print(outfile);
        outfile << ", ";
    } 
}







/*// Function is_full ($$$REMOVED$$$)
// Input: none, const
// Returns: bool
// Does: Compares actual length to capacity
bool ArrayList::is_full() const
{
    return (length >= MAX_PIRATES-1);
}*/






// Function get_length
// Input: none, oncst0
// Returns: int
// Does: Returns the value in length attribute
int ArrayList::get_length() const
{
    return length;
}


void ArrayList::extend()
{
    capacity = capacity * 2;
    Pirate *new_pirates = new Pirate[capacity];
    cout << "Expand to " << capacity << endl;

    for (int i = 0; i < get_length(); i++)
    {
        new_pirates[i] = pirates[i];
    }
    delete[] pirates;

    pirates = new_pirates;
   
}

void ArrayList::shrink()
{
    capacity = capacity / 2;
    Pirate *new_pirates = new Pirate[capacity];
    cout << "Contract to " << capacity << endl; 
    for (int i = 0; i < get_length(); i++)
    {
        new_pirates[i] = pirates[i];
    }
    delete[] pirates;

    pirates = new_pirates;
}








