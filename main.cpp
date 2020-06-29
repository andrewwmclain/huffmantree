/*
 Filename: main.cpp
 Description: main cpp file for running Huffman tree implementation
 Author: Andrew McLain
 Date: 06/3/2020
 Course: Data Structures II
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>
#include <cstring>
#include <sstream>
#include "treenode.h"
#include "BuildMap.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::cerr;
using std::stringstream;

int main(int argc, char const *argv[]){

    //check for valid number of arguments
    if(argc < 4){
        cerr << "Invalid arguments" << endl;
        return -1;
    }

    //if command line argument is -encode, encode
    if(string(argv[1]) == "-encode") {

        //open CL argument input file/encoded output file, terminate if invalid
        string inputFile = argv[2];
        std::ifstream fin(inputFile);

        if(!fin.is_open()){
            cerr << "Invalid input file" << endl;
            return -1;
        }

        string encodedOutputFile = argv[3];
        std::ofstream foutEncoded(encodedOutputFile);

        if(!foutEncoded.is_open()){
            cerr << "Invalid output file" << endl;
            return -1;
        }

        //make frequency map of char int pairs from input file
        std::map<char, int> m;

        char c;
        while (fin.good()) {
            c = fin.get();
            if (!fin.fail()) {
                if (m.find(c) == m.end()) {
                    m.emplace(c, 1);
                } else {
                    m[c]++;
                }
            }
        }

        fin.close();

        //make frequency vector of int char pairs from frequency map and sort by frequency
        vector <std::pair<int, char>> v;
        std::map<char, int>::iterator it;

        for (it = m.begin(); it != m.end(); it++) {
            v.push_back(std::make_pair(it->second, it->first));
        }

        sort(v.begin(), v.end());

        //make vector of treenodes from frequency vector
        vector<TreeNode*> treeVec;

        for (int i = 0; i < v.size(); ++i) {
            treeVec.push_back(new TreeNode(v[i].first, v[i].second, nullptr, nullptr));
        }

        int sumFreq = 0;
        size_t insertIndex = 0;

        //add nodes from frequency vector and add parent nodes for binary tree into treeVec
        for (size_t i = 0; i < v.size(); i += 2) {
            if (i < v.size() - 1) {
                insertIndex = 0;
                //frequency of parent node = sum of frequency of children
                sumFreq = v[i].first + v[i + 1].first;
                //find where to insert new parent node based on frequency
                while (insertIndex < v.size() && v[insertIndex].first < sumFreq) {
                    insertIndex++;
                }
                //insert parent node values into frequency vector
                v.insert(v.begin() + insertIndex, std::make_pair(sumFreq, '\0'));
                //insert new parent node into treeVec
                treeVec.insert(treeVec.begin() + insertIndex,
                               new TreeNode(sumFreq, '\0', treeVec[i], treeVec[i + 1]));
            }
        }


        //create map to represent code table from constructed binary tree
        std::map<char, string> binMap;
        string s1 = "";
        buildMap(binMap, s1, treeVec[treeVec.size() - 1]);


        //print table to output in order of descending frequency
        for (int i = (v.size() - 1); i >= 0; --i) {
            if (v[i].second == '\n') {
                cout << "{key: CR, code: " << binMap['\n'] << "}" << endl;
            } else if (v[i].second == '\r') {
                cout << "{key: LF, code: " << binMap['\r'] << "}" << endl;
            } else if (v[i].second != '\0') {
                cout << "{key:  " << v[i].second << ", code: " << binMap[v[i].second] << "}" << endl;
            } else {

            }
        }

        //print table values to beginning of encoded file for DECODING
        //THIS CODE MUST BE COMMENTED OUT IF YOU WANT ENCODED OUTPUT TO MATCH PERFECTLY
        for (auto const& x: binMap){
            foutEncoded << x.second << " " << x.first << " ";
        }
        foutEncoded << endl;


        //take in input file and use encoding table to output into encoded output file
        std::ifstream fin2(inputFile);

        //encode input file and print to output file
        while (fin2.good()) {
            c = fin2.get();
            if (!fin2.fail()) {
                foutEncoded << binMap[c];
            }
        }
        fin2.close();
        foutEncoded.close();

        //clear dynamically allocated heap memory
        for(size_t i = 0; i < treeVec.size(); ++i){
            delete treeVec[i];
        }

    }
    //for decoding
    else if(string(argv[1]) == "-decode"){
        //open CL argument encoded input/decoded output files, terminate if invalid
        string encodedInputFile = argv[2];
        std::ifstream finEncoded(encodedInputFile);

        if(!finEncoded.is_open()){
            cerr << "Invalid input file" << endl;
            return -1;
        }

        string decodedOutputFile = argv[3];
        std::ofstream foutDecoded(decodedOutputFile);

        if(!foutDecoded.is_open()){
            cerr << "Invalid output file" << endl;
            return -1;
        }

        //create map of string codes (keys) with associated chars (values)
        std::map<string, char> binMap2;

        string code;
        char key;
        int enterCount = 0;

        //build decoding map from encoded file
        while(finEncoded.good()){
            code += finEncoded.get();
            if(code == "\n"){
                break;
            }
            if(code[code.size() - 1] == ' '){
                key = finEncoded.get();
                code.erase(code.size() - 1, 1);
                binMap2.emplace(code, key);
                code.clear();
                finEncoded.get();
            }
        }


        string nextCode = "";

        //decode encoded input file
        while (finEncoded.good()) {
            nextCode += finEncoded.get();
            if (!finEncoded.fail()) {
                //if code not found, keep adding numbers to code
                if(binMap2.find(nextCode) == binMap2.end()) {
                }
                else{
                    foutDecoded << binMap2[nextCode];
                    nextCode.clear();
                }
            }
        }

        finEncoded.close();
        foutDecoded.close();
    }
    //neither encoding nor decoding indicated, terminate program
    else{
        cerr << "Invalid arguments" << endl;
        return -1;
    }
    return 0;
}