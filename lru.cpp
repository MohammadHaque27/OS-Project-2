
#include "policies.hpp"
#include "dataStructures.cpp"
#include<iostream>
#include<cstdlib>
#include <string>
#include <vector>


//Function for the LRU Algorithm
void lru(int frame_num, std::vector<int> &array_object)
{
    /*
    //use a different class for each page table object based on what the replacement algorithm needs
    CircularArray pageTable(nframes);
    
    FILE * tracefile;
    tracefile = fopen(traceName, "r");
    
    unsigned addr; 
    char rw;
    while (fscanf(tracefile,"%x %c",&addr,&rw) != 0)
    {
        addr = 0x(addr) / 4096; //Extract frame number by removing the 12 offset bits
        //loop to compare addr to each page table entry
    }
    fclose(tracefile);
    */
    
    
    
    
    // if the page is not in LRU and the LRU is full
    //pop the front of the array 
    //add the new page to the back
    int temp = frame_num;
    array_object.erase(array_object.begin());
    for(int i = 0; i=<len(array_object); i++){
        array_object[i+1] = array_object[i]; // pushes each item 1 position to the left

    }
    array_object.push_back(temp);// adds the temp to the last postion of the array
    std:: << cout << array_object;
}
