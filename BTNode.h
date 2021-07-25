//BTNode.h
//SENG1120
//Written by: Jeremy Anderson c3315176
//Updated: 18/11/20
//Designed for use with files related c3315176.zip for A3
//BTNode class:   holds data for item, and links to
//              left, right and parent nodes
//              to form functional basis of BSTree
//This is the definition/profile and implementation

#ifndef BTNODE_H
#define BTNODE_H

#include <cstdlib> //used for NULL
#include <string>

using namespace std;

template <typename Item>
class BTNode {
public:
    //constructor
    BTNode(const Item& init_data = Item(), BTNode* init_parent = NULL, BTNode* init_left = NULL, BTNode* init_right = NULL){
        data = init_data;
        parent = init_parent;
        left = init_left;
        right = init_right;
    }
    //destructor
    ~BTNode() {
        left = NULL;
        right = NULL;
        parent = NULL;
    }

    /** Mutator member functions **/
    //set_data
    //Pre-conditions: receives Item for data to manipulate data entry
    //post-conditions: data is updated using received data
    void set_data(const Item& new_data)     { data = new_data; }

    //set_left
    //Pre-conditions: receives entry for a node link
    //Post-conditions: link to left node is created
    void set_left(BTNode* left_link)        { left = left_link; }

    //set_right
    //Pre-conditions: receives entry for a node link
    //Post-conditions: link to right node is created
    void set_right(BTNode* right_link)      { right = right_link; }

    //set_parent
    //Pre-conditions: receives entry for a node link
    //Post-conditions: link to parent node is created
    void set_parent(BTNode* parent_link)      { parent = parent_link; }

    /** Query member functions **/
    //get_data
    //Pre-conditions: none
    //Post-conditions: receives data of Item for specified node
    Item get_data() const                   { return data; }

    //get_left const
    //Pre-conditions: none
    //Post-conditions: receives left node link of specified node
    const BTNode* get_left() const          { return left; }

    //get_left
    //Pre-conditions: none
    //Post-conditions: receives left node link of specified node
    BTNode* get_left()                      { return left; }

    //get_right const
    //Pre-conditions: none
    //Post-conditions: receives right node link of specified node
    const BTNode* get_right() const         { return right; }

    //get_right
    //Pre-conditions: none
    //Post-conditions: receives right node link of specified node
    BTNode* get_right()                     { return right; }

    //get_parent const
    //Pre-conditions: none
    //Post-conditions: receives parent node link of specified node
    const BTNode* get_parent() const         { return parent; }

    //get_parent
    //Pre-conditions: none
    //Post-conditions: receives parent node link of specified node
    BTNode* get_parent()                     { return parent; }

    //is_leaf
    //Pre-conditions: requires at least one node in the tree
    //Post-conditions: returns true if specified node does not have children
    bool is_leaf() const            { return (left == NULL) && (right == NULL); }

    //has_one_child
    //Pre-conditions: a "parent" node exists
    //Post-conditions: returns true if specified node has only have children
    bool has_one_child() const      { return ((left == NULL) && (right != NULL)) ||
                                             ((left != NULL) && (right == NULL)); }
    //is_right_child
    //Pre-conditions: a parent node and child node exists
    //Post-conditions: returns true if specified node is a right child
    bool is_right_child() const     { return data > parent->get_data(); }


private:
    //data for Item & pointers to left/right child
    Item data;
    BTNode* left;
    BTNode* right;
    BTNode* parent;
};

#endif
