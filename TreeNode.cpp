/*
 Filename: TreeNode.cpp
 Description: Defines the constructor and destructor for the TreeNode class
 Author: Andrew McLain
 Date: 06/3/2020
 Course: Data Structures II
*/
#include "TreeNode.h"

//TreeNode constructor
//constructs tree node from frequency, name, and left/right children pointers
//@param freq, the frequency of the character in the tree node
//@param *left, the left child of the tree node
//@param *right, the right child of the tree node
//@returns nothing
TreeNode::TreeNode(int freq, char name, TreeNode *left, TreeNode *right) :
                   _freq(freq), _name(name), _left(left), _right(right){

}

//TreeNode destructor
//@param none
//@returns nothing
TreeNode::~TreeNode(){

}