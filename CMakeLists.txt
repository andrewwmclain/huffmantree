cmake_minimum_required(VERSION 3.10)
project(huffman_andrewwmclain)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(huffman_andrewwmclain
        .gitignore
        README.md main.cpp TreeNode.cpp TreeNode.h BuildMap.cpp BuildMap.h)
