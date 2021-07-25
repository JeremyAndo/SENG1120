//HTable.h
//SENG1120
//Written by: Jeremy Anderson c3315176
//Updated: 18/11/20
//Designed for use with files related c3315176.zip for A3
//HTable class: hash function that inserts
//              to an array, based on storing type item
//This is the definition/profile

#ifndef HTABLE_H
#define HTABLE_H

#include <cstdlib>
#include <ostream>

template <typename Item>
class HTable {
public:
    //Constructor
    HTable();

    //Destructor
    ~HTable();

    //Member functions

    //add
    //pre: takes in an item, htable must exist
    //post: item is added using hash function
    void add(const Item& data);

    //remove
    //pre: takes in an item, htable must exist
    //post: removes item from htable by setting it to "NULL"
    bool remove(const Item& data);

    //inOrder
    //pre: htable must exist
    //post: prints array from 0 to n, excludes all "NULL" elements
    Item inOrder() const;

    //Overloaded +=
    void operator += (HTable<Item> hashTable2);

private:
    int capacity;
    //hash function
    //pre: takes in an item
    //post: assigns it a value within the array bounds
    int hashFun(Item value);
    Item* hash_table;


};

//Overloaded <<
template <typename Item>
std::ostream& operator << (std::ostream& out, HTable<Item> hashTable);

#include "HTable.hpp"

#endif