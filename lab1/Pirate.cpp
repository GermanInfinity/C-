/*
 * Pirate.cpp
 * COMP15
 * Fall 2018
 *
 * Implarrrrrrmentation of a Pirate
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

void Pirate::print(ostream &outfile) const //Modified print function. 
{
    outfile << pirate_id << " " << name << endl; 

    //cout << pirate_id << " "
        //<< name << " " << endl;
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

//Function to generate next pirate name in order. As opposed to random!

void Pirate::generate_next_pirate(ifstream &infile)
{
    string pirate_name;

    if (getline(infile, pirate_name)){
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

