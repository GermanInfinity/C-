/*
 * PirateMates.h
 * Akwarandu Ugo Nwachuku
 * 17th September, 2018
 * COMP 15 HW1
 * This is the interface for the pirate mates structure. It declares a Pirate 
 * object pirate and an ArrayList object mates. 
 * yo ho ho
 */

#include <fstream>
#include <string>
#include "Pirate.h"
#include "ArrayList.h"
using namespace std;

#ifndef PIRATE_MATES_H_
#define PIRATE_MATES_H_


struct PirateMates{
  Pirate pirate;
  ArrayList mates;
};


#endif
