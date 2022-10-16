#include "policies.hpp"
#include "dataStructures.hpp"


void VMS(std::string traceName, int nframes, int p) //traceName may need to be (const char*)
{
    //conditional to just run fifo or lru (figure out percentages)
    //if (p == 100)

    CircularArray buffer1(nframes);
    //create buffer2

    FILE * tracefile;
    tracefile = fopen(traceName, "r");
    
    unsigned addr; 
    char rw;
    while (fscanf(tracefile,"%x %c",&addr,&rw) != 0) //use != EOF later instead of != 0
    {
        addr = addr / 4096; //Extract frame number by removing the 12 offset bits
        //loop to compare addr to each page table entry
    }





    fclose(tracefile);
}