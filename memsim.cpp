//#include <iostream>
#include <stdio>
#include <string> //technically already included in a .hpp file
#include "dataStructures.hpp"
#include "policies.hpp"


int main(int argc, char* argv[]) //memsim <tracefile> <nframes> <lru|fifo|vms> <p> <debug|quiet> 
{
    //use a different class for each page table object based on what the replacement algorithm needs
    CircularArray pageTable(argv[1]); //argv[1] = <nframes>
    
    FILE * tracefile;
    tracefile = fopen(argv[0], "r"); //argv[0] = <tracefile>
    
    unsigned addr; 
    char rw;
    while (fscanf(tracefile,"%x %c",&addr,&rw) != 0)
    {
        addr = 0x(addr) / 4096; //Extract frame number by removing the 12 offset bits
        //loop to compare addr to each page table entry
    }





    fclose(argv[0]); //argv[0] = <tracefile>
    
    return 0;
}

