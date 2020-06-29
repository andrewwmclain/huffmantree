/*
 Filename: BuildMap.h
 Description: Declares the buildMap function
 Author: Andrew McLain
 Date: 06/3/2020
 Course: Data Structures II
*/

#ifndef HUFFMAN_ANDREWWMCLAIN_BUILDMAP_H
#define HUFFMAN_ANDREWWMCLAIN_BUILDMAP_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include "treenode.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

void buildMap(std::map<char, string>& m1, string& s1, TreeNode* root);

#endif //HUFFMAN_ANDREWWMCLAIN_BUILDMAP_H
