
#include<iostream>
#include<cstdlib>
#include <string>
#include <vector>
#include "dataStructures.cpp"


//Function for FIFO Algorithm 
void FIFO(int nframes, int frames[7]){
    //use a different class for each page table object based on what the replacement algorithm needs
    CircularArray pageTable(nframes); //passed as argument
    
    // FILE * tracefile;
    // tracefile = fopen(traceName, "r"); //argv[0] = <tracefile>
    
    // unsigned addr; 
    // char rw;
    // while (fscanf(tracefile,"%x %c",&addr,&rw) != 0) //Loop: read each address from trace file
    // {
    //     addr = addr / 4096; //Extract frame number by removing the 12 offset bits
    //     //loop to compare addr to each page table entry
    // }

    // std::cout<< offset << " " << size << " " << position <<  " ";
    // pageTable.incrementLoopOffset();
    // std::cout<< pageTable.getLoopOffset() << " ";

    //std::cout << replacementIndex << frameNum.c_str() << std::endl;

    //This is the replacement policy code if the page isn't found and it isn't empty
        //std::cout << i << " ";
    //     int replacementIndex = pageTable.calculateCircularIndex();
    //     pageTable.array[replacementIndex] = addr;
    //     pageTable.incrementLoopOffset();
    
    


    // std::cout<< "Successfully added\n";
    // for (int i = 0; i < pageTable.getSize(); i++) {
    //     std::cout<< pageTable.array[i] << ", ";
    // }
    

    //std::cout << size << std::endl;
    // fclose(argv[0]); //argv[0] = <tracefile>
}


int main(){
    //int frames[7] = {0x0042bf60, 0x2f293f60, 0x1f16ff60, 0x0041f760, 0x37c1f760, 0x0041f840, 0x0041f860};
    //FIFO(4, frames);
    unsigned address = 0042bf60;
    unsigned addr = address / 4096;
    std::cout<<addr<<" ";

    return 0;
}