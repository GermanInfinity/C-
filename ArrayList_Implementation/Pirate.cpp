/*
 * Pirate.cpp
 * Akwarandu Ugo Nwachuku
 * 17th September, 2018
 * COMP 15 HW1
 *
 * This is the implementation of the Pirate class. It has a number of functions
 * the main ones being generating a pirates name, the next pirate, assigning
 * a pirates ID number and printing out a pirates information. 
 */

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "Pirate.h"
using namespace std;

int Pirate::pirate_count = 0;

Pirate::Pirate()
{
    pirate_id = -1;
    name = "Cap'n Hook";
}

Pirate::Pirate(string n)
{
    assign_pirate_id();
    name = n;
}

void Pirate::print(ostream &outfile) const
{
    outfile << pirate_id << " "
         << name;
}

void Pirate::generate_pirate_name(ifstream &infile, int range)
{
    string pname;
    int rando = rand() % range;
    int count = 0;

    infile.clear();
    infile.seekg(0, ios::beg);
    while (getline(infile, pname))
    {
        if (count == rando)
        {
            name = pname;
            break;
        }
        count++;
    }
}
/* Purpose: This function reads through a file and selects names of pirates.
 * It assigns the name of a pirate to the private variable name, which 
 * represents the pirates name, and it accepts a pointer reference of a file in 
 * memory(where it reads the pirates name from). 
*/
void Pirate::generate_next_pirate(ifstream &infile)
{
    string pirate_name;
    if (getline(infile, pirate_name))
    {
        name = pirate_name;
    }
}

void Pirate::assign_pirate_id()
{
    pirate_id = pirate_count++;
}

bool operator == (const Pirate &p1, const Pirate &p2)
{
    return (p1.pirate_id == p2.pirate_id);
}

