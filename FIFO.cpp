
#include<iostream>
#include<cstdlib>
#include <string>
#include <vector>
#include "dataStructures.cpp"

using namespace std;

//Function for FIFO Algorithm 
void FIFO(CircularArray &pageTable){
    int offset = pageTable.getLoopOffset();
    int size = pageTable.getSize();
    int position = pageTable.calculateCircularIndex();
    std::cout << size << std::endl;
    
}


int main(){
    CircularArray pageTable(4);
    FIFO(pageTable);


    return 0;
}