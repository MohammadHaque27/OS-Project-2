//#include <iostream>
#include <stdio.h>
#include <iostream>
#include <string.h> //technically already included in a .hpp file
// #include "dataStructures.hpp"
#include "policies.hpp"


int main(int argc, char* argv[]) //memsim <tracefile> <nframes> <lru|fifo|vms> <p> <debug|quiet> 
{
    char *tracefile, *algorithm, *debugOrQuiet;
    int nframes;
    int p = 0;

    if(argc<5) {
        std::cout<<"You have too few arguments!"<<std::endl;
    }

    if(argc == 5) {
        if (strcmp(argv[3], "fifo") == 0 || strcmp(argv[3], "lru") == 0){
            tracefile = argv[1];
            nframes = std::atoi(argv[2]);
            algorithm = argv[3];
            debugOrQuiet = argv[4];
        }
        else{
            std::cout << "vms requires the p parameter!" << std::endl;
        }
        
    }

    else if (argc == 6) {
        if (strcmp(argv[3], "vms") == 0) {
            tracefile = argv[1];
            nframes = std::atoi(argv[2]);
            algorithm = argv[3];
            p = std::atoi(argv[4]);
            debugOrQuiet = argv[5];
        }
        else {
            std::cout << "fifo and lru do not require parameter p." << std::endl;
        }
    }

    if(strcmp(algorithm, "fifo") == 0) {
        FIFO(nframes, tracefile, debugOrQuiet);
    }

    else if (strcmp(algorithm, "lru") == 0) {
        lru(tracefile, nframes, debugOrQuiet);
    }

    else if (strcmp(algorithm, "vms") == 0) {
        //PLEASE CALL YOUR FUNCTION
    }

    else {
        std::cout << "You have entered an invalid algorithm" << std::endl;
    }
    
    return 0;
}

