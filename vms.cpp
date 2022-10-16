#include "policies.hpp"
#include "dataStructures.hpp"


void VMS(std::string traceName, int nframes, int p)
{
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
}