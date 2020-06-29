/*
 Filename: BuildMap.cpp
 Description: Defines the buildMap function declared in buildMap.h
 Author: Andrew McLain
 Date: 06/3/2020
 Course: Data Structures II
*/

#include "BuildMap.h"



//Build Map
//builds mapping from code to character based on binary tree
//@param m1, the map to be built
//@param s1, the string to keep track of codes
//@param root, the root node of the tree
//@returns nothing

void buildMap(std::map<char, string>& m1, string& s1, TreeNode* root){
    if(root == nullptr){
        return;
    }
    //leaf node means it is a character that can be mapped to a code
    else if(!root->_left && !root->_right){
        m1.emplace(root->_name, s1);
    }
    //not a leaf node, continue traversing and adding to code based on edges traveled
    else{
        //left edge = 1
        if(root->_left){
            s1.append("1");
            buildMap(m1, s1, root->_left);
        }
        //right edge = 0
        if(root->_right){
            s1.append("0");
            buildMap(m1, s1, root->_right);
        }
    }
    //subtract the value added from the edge when you return up to that edge
    if(!s1.empty()){
        s1 = s1.substr(0, s1.size() - 1);
    }
}
