/*
 * Filename: ActualNode.h
 * Contains: Interface for actual node located as a vector in HashNode
 * Part of: Project 2
 *
 */

#ifndef ACTUALNODE_H_
#define ACTUALNODE_H_

#include "Loc_Values.h"
#include "Value.h"
#include "HashNode.h"

struct ActualNode
{
    string key;
    //Value value; //to handle occurences
    vector<Loc_Values> location;
};

#endif
