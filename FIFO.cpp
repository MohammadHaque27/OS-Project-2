
#include<iostream>
#include<cstdlib>
#include <string>
#include <vector>
#include "dataStructures.cpp"


//Function for FIFO Algorithm 
void FIFO(CircularArray &pageTable, std::string frameNum){
    int offset = pageTable.getLoopOffset();
    int size = pageTable.getSize();
    int position = pageTable.calculateCircularIndex();
    // std::cout<< offset << " " << size << " " << position <<  " ";
    // pageTable.incrementLoopOffset();
    // std::cout<< pageTable.getLoopOffset() << " ";
    int replacementIndex = pageTable.calculateCircularIndex();
    //std::cout << replacementIndex << frameNum.c_str() << std::endl;
    std::cout << *pageTable.array << " ";
    pageTable->array + replacementIndex = frameNum;

    
    std::cout<< "Successfully added\n";
    std::cout<< pageTable.array[replacementIndex] << " ";

    //std::cout << size << std::endl;
    
}


int main(){
    CircularArray pageTable(4);
    FIFO(pageTable, "Hello");
    

    return 0;
}