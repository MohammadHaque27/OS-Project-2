//#include <iostream>
#include <stdio>
#include "dataStructures.hpp"
#include "policies.hpp"


int main(int argc, char* argv[]) //memsim <tracefile> <nframes> <lru|fifo|vms> <p> <debug|quiet> 
{
    FILE * tracefile;
    tracefile = fopen(argv[0], "r"); //argv[0] = <tracefile>
    
    unsigned addr; //Wanwan had type unsigned
    char rw; //had .. after this 
    fscanf(tracefile,"%x %c",&addr,&rw);






    fclose(argv[0]); //argv[0] = <tracefile>
    
    return 0;
}

