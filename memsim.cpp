//#include <iostream>
#include <stdio>
#include <string> //technically already included in a .hpp file
#include "dataStructures.hpp"
#include "policies.hpp"


int main(int argc, char* argv[]) //memsim <tracefile> <nframes> <lru|fifo|vms> <p> <debug|quiet> 
{
    CircularArray(argv[1]); //argv[1] = <nframes>
    
    FILE * tracefile;
    tracefile = fopen(argv[0], "r"); //argv[0] = <tracefile>
    
    std::string addr; //Wanwan had as type unsigned
    char rw;
    while (fscanf(tracefile,"%x %c",&addr,&rw) != 0)
    {
        addr.erase(addr.end()-3, addr.end()); //right hex digit shift by 3
        //loop to compare addr to each page table entry
    }






    fclose(argv[0]); //argv[0] = <tracefile>
    
    return 0;
}

