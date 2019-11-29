/*
 * Filename: Nodetype.h
 * Contains: Interface for node in dynamic array of index
 * Part of: Project 2
 *
 */

#ifndef HASHNODE_H_
#define HASHNODE_H_

#include "Loc_Values.h"
#include "ActualNode.h"
#include "Value.h"

struct HashNode
{
    string key;
    vector<ActualNode> vec_ptr;

};

#endif
