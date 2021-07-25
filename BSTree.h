//BSTree.h
//SENG1120
//Written by: Jeremy Anderson c3315176
//Updated: 18/11/20
//Designed for use with files related c3315176.zip for A3
//BSTree class: data structure storing BTNodes to form
//              a binary search tree
//This is the definition/profile


#ifndef BSTREE_H
#define BSTREE_H

#include <cstdlib>
#include "BTNode.h"

template <typename Item>
class BSTree
{
public:
    //Constructor
    //Pre: none
    //Post: creates BSTree with no nodes
    BSTree();
    //Pre: none
    //Post: creates BSTree with root node
    BSTree(const Item& data);

    //Destructor
    //Pre: BSTree exists
    //Post: removes nodes
    ~BSTree();

    //Member functions

    //size
    //Pre: none
    //Post: returns amount of nodes
    size_t size();

    //add
    //Pre: supplied with Item to add to Tree
    //Post: adds item to tree
    void add(const Item& data);

    //root
    //pre: root node exists
    //post: root node data returned
    Item root() const;

    //printInOrder
    //pre:
    //post:
    void printInOrder();

    //find
    //pre: supplied with item to target search
    //post: true if item exists, false otherwise
    bool find(const Item& target) const;

    //remove
    //pre: supplied with item to target search
    //post: if found, remove item, else return false
    bool remove(const Item& data);

    //Overloaded +=
    void operator += (BSTree<Item> tree2);

private:
    //Members
    size_t nodes;
    BTNode<Item>* root_;

    //Functions

    //recursive to add member function
    void BSTreeAdd(BTNode<Item>* current_node, const Item& data);
    //recursive to printInOrder member function
    void BSTreeInOrder(BTNode<Item>* node, int tree_level);
    //compare
    //pre: takes in two different items
    //post: returns result of -1, 0 or 1 based on values of items in comparison
    int compare(const Item& a, const Item& b) const;
    //recursive to find member function
    bool BSTreeFind(BTNode<Item>* current_node, const Item& target) const;
    //recursive to remove member function
    bool BSTreeRemove(BTNode<Item>* current_node, const Item& data);
    //findMin - recursive
    //pre: takes in a tree in the form of a parent node
    //post: recursive search to return item at left most side of tree
    BTNode<Item>* findMin(BTNode<Item>* current_node);
};

//Overloaded <<
template <typename Item>
ostream& operator << (ostream& out, BSTree<Item> tree);

#include "BSTree.hpp"

#endif