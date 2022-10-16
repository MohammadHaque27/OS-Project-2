
#include<iostream>
#include<cstdlib>
#include <string>
#include <vector>
#include "dataStructures.hpp"

using namespace std;

//Function for FIFO Algorithm 
void FIFO(CircularArray* pageTable){
    int offset = *pageTable.getLoopOffset();
    int size = pageTable.getSize();
    int position = offset % size;

    
}


