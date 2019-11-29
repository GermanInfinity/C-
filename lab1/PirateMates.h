/*
 * PirateMates.h
 * COMP15
 * Fall 2018
 *
 * Interface for Pirate mates class
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
  ArrayList pirates_mates;
}


#endif
