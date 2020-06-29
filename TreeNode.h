/*
 Filename: TreeNode.h
 Description: Defines the TreeNode class data members and declares constructor and destructor
 Author: Andrew McLain
 Date: 06/3/2020
 Course: Data Structures II
*/
#ifndef HUFFMAN_ANDREWWMCLAIN_TREENODE_H
#define HUFFMAN_ANDREWWMCLAIN_TREENODE_H

#include <string>
using std::string;

class TreeNode {
public:
    int _freq;
    char _name;
    TreeNode* _left;
    TreeNode* _right;

    TreeNode(int freq, char name, TreeNode* left, TreeNode* right);
    ~TreeNode();
};


#endif //HUFFMAN_ANDREWWMCLAIN_TREENODE_H
