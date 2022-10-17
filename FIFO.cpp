
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stdio.h>
#include "dataStructures.cpp"


//Function for FIFO Algorithm 
void FIFO(int nframes, const char* traceName){
    //use a different class for each page table object based on what the replacement algorithm needs
    CircularArray pageTable(nframes); //passed as argument
    
    FILE * tracefile;
    tracefile = fopen(traceName, "r"); //argv[0] = <tracefile>
    
    unsigned addr; 
    unsigned frameNum;
    char rw;
    int hits = 0;
    while (fscanf(tracefile,"%x %c",&addr,&rw) != EOF) //Loop: read each address from trace file
    {
        frameNum = addr / 4096; //Extract frame number by removing the 12 offset bits
        std::cout << frameNum << " ";
        //loop to compare addr to each page table entry
        for (int i = 0; i < pageTable.getSize(); i++) {
            std::cout << pageTable.array[i].first << "\n";
            if (frameNum == pageTable.array[i].first)
            {
                hits++;
                if ((pageTable.array[i].second != 'W') && (rw == 'W'))
                {
                    pageTable.array[i].second = rw;
                }
                std::cout<<"Frame is in page table\n";
                break;
            }
            else if (pageTable.array[i].first == 0)//Check if page table is empty
            {
                pageTable.array[i].first = frameNum;
                std::cout<<"Table entry " << i << " is empty, adding frame to the table\n";
                break;
            }
            else if (i < (pageTable.getSize()-1)){
                continue;
            }
            else {
                //std::cout << "Table is full, replacing the oldest entry\n";
                int replacementIndex = pageTable.calculateCircularIndex();
                pageTable.array[replacementIndex].first = frameNum;
                pageTable.incrementLoopOffset();
            }


        }
        

    }
    std::cout<<"test";

    //This is the replacement policy code if the page isn't found and it isn't empty

    
    


    // std::cout<< "Successfully added\n";
    for (int i = 0; i < pageTable.getSize(); i++) {
        std::cout << pageTable.array[i].first << ", ";
    }
    std::cout << hits << ".";
    

    //std::cout << size << std::endl;
    fclose(tracefile); //argv[0] = <tracefile>
}


int main(){
    //int frames[7] = {0x0042bf60, 0x2f293f60, 0x1f16ff60, 0x0041f760, 0x37c1f760, 0x0041f840, 0x0041f860};
    FIFO(4, "test.trace");

    return 0;
}