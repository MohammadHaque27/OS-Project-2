#include "policies.hpp"
#include "dataStructures.hpp"


void VMS(std::string traceName, int nframes, int p) //traceName may need to be (const char*)
{
    int size2 = (nframes * p) / 100;
    int size1 = nframes - size2;

    //conditional to just run fifo or lru (figure out percentages)
    //if (size1 == 0)

    CircularArray buffer1(size1);
    //create buffer2

    FILE * tracefile;
    tracefile = fopen(traceName, "r");
    
    unsigned addr; 
    unsigned frameNum;
    char rw;
    while (fscanf(tracefile,"%x %c",&addr,&rw) != EOF)
    {
        frameNum = addr / 4096; //Extract frame number by removing the 12 offset bits
        //loop to compare addr to each page table entry
    }





    fclose(tracefile);
}