#include "policies.hpp"
#include "dataStructures.hpp"


void VMS()
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