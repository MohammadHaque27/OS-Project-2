
#include policies.hpp
#include dataStructures.cpp
#include<iostream>
#include<cstdlib>
#include <string>
#include <vector>


//Function for the LRU Algorithm
void lru(int frame_num, std::vector<int> &array_object)
{
    // if the page is not in LRU and the LRU is full
    //pop the bottom of the array 
    //add the new page to the top
    int temp = frame_num;
    array_object.erase(array_object.begin());
    array_object.push_back(temp);
}
