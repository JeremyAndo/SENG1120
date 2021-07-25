//BSTree.h
//SENG1120
//Written by: Jeremy Anderson c3315176
//Updated: 18/11/20
//Designed for use with files related c3315176.zip for A3
//BSTree class: data structure storing BTNodes to form
//              a binary search tree
//This is the implementation


#include <cassert>
#include <iostream>

using namespace std;

template <typename Item>
BSTree<Item>::BSTree() {
    nodes = 0;
    root_ = NULL;
}

template <typename Item>
BSTree<Item>::BSTree(const Item& data) {
    nodes = 1;
    root_ = new BTNode<Item>(data);
}

template <typename Item>
BSTree<Item>::~BSTree() {
    //figure out later
    //create recursive function
    //if node == null return
    //remove nodes (recursive left), then same for right side
    //delete node
    //size--
}

template <typename Item>
std::size_t BSTree<Item>::size() {
    return nodes;
}

template <typename Item>
Item BSTree<Item>::root() const {
    return root_->get_data();
}

template <typename Item>
void BSTree<Item>::add(const Item &data) {
    //if root node does not exist, add root node
    if (root_ == NULL){
        root_ = new BTNode<Item>(data);
        nodes++;
    }
    //else add normally (recursive)
    else
        BSTreeAdd(root_, data);
}

template <typename Item>
void BSTree<Item>::BSTreeAdd(BTNode<Item>* current_node, const Item &data) {

    //1. compare current node to data being inserted
    int relation = compare(data, current_node->get_data());

    //2. if the same, replace existing data
    if (relation == 0)
        current_node->set_data(data);

    //3. add to right side of tree (insert data is greater than current node)
    else if (relation > 0){

        if (current_node->get_right() == NULL){ //if right child empty, add
            current_node->set_right(new BTNode<Item>(data, current_node));
            nodes++;
            return;
        }
        else //if right child is occupied, recursive call
            BSTreeAdd(current_node->get_right(), data);
    }

    //4. add to left side of tree (insert data is less than current node)
    else {

        if (current_node->get_left() == NULL){ //if left child empty, add
            current_node->set_left(new BTNode<Item>(data, current_node));
            nodes++;
            return;
        }
        else //if left child is occupied, recursive call
            BSTreeAdd(current_node->get_left(), data);
    }

}

template <typename Item>
int BSTree<Item>::compare(const Item& a, const Item& b) const
{
    if (a < b)          { return -1; }

    else if (a == b)    { return 0; }

    else                { return 1; }
}

template <typename Item>
void BSTree<Item>::printInOrder(){
    BSTreeInOrder(root_, 0);
}

template <typename Item>
void BSTree<Item>::BSTreeInOrder(BTNode<Item>* node, int tree_level) {
    if (node != NULL) {

        //print left side of tree
        BSTreeInOrder(node->get_left(), tree_level+1);

        /**old code, not needed for A3
        //print node and indent to indicate tree level
        //for (int i = 1; i <= tree_level; i++)
            //cout << " |_";
        cout << node->get_data() << endl;
        */

        //new code - simply prints node with space between
        cout << node->get_data() << " ";


        //print right side of tree
        BSTreeInOrder(node->get_right(), tree_level+1);
    }

    return;
}

template <typename Item>
bool BSTree<Item>::find(const Item& target) const{
    if (nodes == 0)
        return false;
    else
        return BSTreeFind(root_, target);
}

template <typename Item>
bool BSTree<Item>::BSTreeFind(BTNode<Item>* current_node, const Item& target) const{
    //base case
    if (current_node == NULL)
        return false;
    else {
        int relation = compare(target, current_node->get_data());

        if (relation == 0)
            return true;
        else if (relation < 0)
            return BSTreeFind(current_node->get_left(), target);
        else
            return BSTreeFind(current_node->get_right(), target);
    }
}

template <typename Item>
bool BSTree<Item>::remove(const Item &data) {
    if (nodes == 0)
        return false;
    else
        return BSTreeRemove(root_, data);
}

template <typename Item>
bool BSTree<Item>::BSTreeRemove(BTNode<Item> *current_node, const Item &data) {
    //node does not exist in tree
    if (current_node == NULL)
        return false;

    int relation = compare(data, current_node->get_data());

    //recursive to search right side
    if (relation > 0)
        BSTreeRemove(current_node->get_right(), data);
    //recursive to search left side
    else if (relation < 0)
        BSTreeRemove(current_node->get_left(), data);

    //if node is found, cases to remove
    else {
        /** CASE 1 - LEAF */
        if (current_node->is_leaf()){

            /** Root node */
            if (compare(root_->get_data(), data) == 0 )
                root_ = NULL;

            /** Normal nodes - adjust parent links */
            else {
                //remove parent link to child
                if (current_node->is_right_child())
                    current_node->get_parent()->set_right(NULL);
                else
                    current_node->get_parent()->set_left(NULL);
            }

            //release leaf node from memory
            delete current_node;
            nodes--;
        }

        /** CASE 2 - ONE CHILD*/
        else if (current_node->has_one_child()){

            /** root node */
            if (compare(root_->get_data(), data) == 0){ //change root to right node
                if (current_node->get_right() != NULL){
                    current_node->get_right()->set_parent(NULL);
                    root_ = current_node->get_right();
                } else { //change root to left node
                    current_node->get_left()->set_parent(NULL);
                    root_ = current_node->get_left();
                }
            }

            /** node removed has right child */
            else if (current_node->get_right() != NULL){
                //reset internal tree links accordingly
                current_node->get_right()->set_parent(current_node->get_parent());
                if (current_node->is_right_child())
                    current_node->get_parent()->set_right(current_node->get_right());
                else
                    current_node->get_parent()->set_left(current_node->get_right());
            }

            /** node removed has left child */
            else {
                //reset internal tree links accordingly
                current_node->get_left()->set_parent(current_node->get_parent());
                if (current_node->is_right_child())
                    current_node->get_parent()->set_right(current_node->get_left());
                else
                    current_node->get_parent()->set_left(current_node->get_left());
            }

            /** release memory for removed node*/
            delete current_node;
            nodes--;
        }

        /** CASE 3 - TWO CHILDREN */
        else {
            //smallest value in right tree
            BTNode<Item>* temp_node = findMin(current_node->get_right());
            //copy its data
            Item* temp_item = new Item (temp_node->get_data());
            //remove the node
            BSTreeRemove(current_node->get_right(), temp_node->get_data());
            //set copied data to current node
            current_node->set_data(*temp_item);
        }
        //node was removed successfully
        return true;
    }
    //node was not removed
    return false;
}

template <typename Item>
BTNode<Item>* BSTree<Item>::findMin(BTNode<Item>* current_node){
    if (current_node->get_left() != NULL)
        return findMin(current_node->get_left());
    else
        return current_node;
}

template <typename Item>
void BSTree<Item>::operator += (BSTree<Item> tree2){
    BSTree<Item> temp_tree = tree2;
    //loop, add root to new tree, remove it from temp tree, cycle till temp tree is empty
    while (temp_tree.size() != 0){
        add(temp_tree.root());
        temp_tree.remove(temp_tree.root());
    }
}

template <typename Item>
ostream& operator << (ostream& out, BSTree<Item> tree){
    tree.printInOrder();
    return out;
}