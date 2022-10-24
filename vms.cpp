#include "policies.hpp"


void VMS(char* traceName, int nframes, int p, char *debugOrQuiet)
{
    int size2 = (nframes * p) / 100;
    int size1 = nframes - size2;

    if(strcmp(debugOrQuiet, "debug") == 0){
        std::cout<< "size1: " << size1 << std::endl;
        std::cout<< "size2: " << size2 << std::endl;
    }
    
    //conditional to just run fifo or lru
    if (size1 <= 1)
    {
        lru(traceName, nframes, debugOrQuiet);
    }
    else if (size2 <= 1)
    {
        FIFO(nframes, traceName, debugOrQuiet);
    }
    else
    {
        std::vector<int>::iterator It1;
        std::vector<int> buffer1;
        std::map<int, char> dirty1;
        std::vector<int>::iterator It2;
        std::vector<int> buffer2;
        std::map<int, char> dirty2;
        //int bufferHits = 0; //what do I need this for again?
        int diskReads = 0;
        int diskWrites = 0;
        int count = 0;

        FILE * tracefile;
        tracefile = fopen(traceName, "r");
        
        unsigned addr; 
        unsigned frameNum;
        char rw;
        //loop over each memory address in trace file
        while (fscanf(tracefile,"%x %c",&addr,&rw) != EOF)
        {
            count++;
            frameNum = addr / 4096; //Extract frame number by removing the 12 offset bits
            //loop to compare frameNum to each page table entry
            int code1;
            It1 = find(buffer1.begin(), buffer1.end(), frameNum); //Look for a frameNum match
            if(It1 == buffer1.end()) //set switch code1 for frame not in FIFO table
            {
                code1 = 2;  
            }
            else  //set switch code1 for frame in FIFO table
            {
                code1 = 1;
            } 
                
            switch(code1) 
            {
                case 1: //frame is in FIFO table
                    if(strcmp(debugOrQuiet, "debug") == 0){
                        std::cout<< count <<": Buffer1 entry is a match" << std::endl;
                    }
                    if((dirty1[frameNum] != 'W') && (rw == 'W'))   
                    {
                        dirty1[frameNum] = rw;
                    }
                    break;

                case 2: //frame not in FIFO table
                    if(dirty1.size() < size1) //if FIFO table not full
                    {
                        diskReads++;
                        if(strcmp(debugOrQuiet, "debug") == 0){
                            std::cout<< count <<": Buffer1 entry is empty, adding frame to the table" << std::endl;
                        }
                        buffer1.push_back(frameNum);
                        dirty1[frameNum] = rw;
                    }
                    else //FIFO table is full...
                    {
                        //...search through LRU table
                        if(strcmp(debugOrQuiet, "debug") == 0){
                            std::cout<< count <<": Buffer1 is full with no matches, begin searching buffer2" << std::endl;
                        }
                        int code2;
                        It2 = find(buffer2.begin(), buffer2.end(), frameNum); //Look for a frameNum match
                        if(It2 == buffer2.end()) //set switch code2 for frame not in LRU table 
                        {
                            code2 = 1; //note that these code numbers are opposite for code1, this is to keep the nested logic easier to read
                        }
                        else  //set switch code2 for frame in LRU table
                        {
                            code2 = 2;
                        } 
                        
                        switch(code2) 
                        {
                            case 1: //frame not in LRU table
                                diskReads++;
                                if(dirty2.size() < size2) //if LRU table not full
                                {
                                    if(strcmp(debugOrQuiet, "debug") == 0){
                                        std::cout<< count <<": Buffer2 entry is empty, adding frame to the table" << std::endl;
                                    }
                                    buffer2.push_back(frameNum);
                                    dirty2[frameNum] = rw;
                                }
                                else //LRU table is full
                                {
                                    if(strcmp(debugOrQuiet, "debug") == 0){
                                        std::cout<< count <<": Buffer2 is full with no matches, adding frame to buffer1 and shifting buffer1 replacement to buffer2" << std::endl;
                                    }
                                    unsigned tempFrame = buffer1.front();
                                    char tempRW = dirty1[buffer1.front()];

                                    buffer1.erase(buffer1.begin());
                                    dirty1.erase(tempFrame);
                                    buffer1.push_back(frameNum);
                                    dirty1[frameNum] = rw;
                                    
                                    if(dirty2[buffer2.front()] == 'W')
                                    {
                                        diskWrites++;
                                    }

                                    dirty2.erase(buffer2.front());
                                    buffer2.erase(buffer2.begin());
                                    //push replaced buffer1 frame into the back of LRU table (buffer2)
                                    buffer2.push_back(tempFrame);
                                    dirty2[tempFrame] = tempRW;
                                }
                                break;

                            case 2: //frame is in LRU table
                                if(strcmp(debugOrQuiet, "debug") == 0){
                                    std::cout<< count <<": Buffer2 entry is a match, moving this entry to buffer1" << std::endl;
                                }
                                unsigned tempFrame = buffer1.front();
                                char tempRW = dirty1[buffer1.front()];
                                
                                if((dirty2[frameNum] != 'W') && (rw == 'W'))   
                                {
                                    dirty2[frameNum] = rw;
                                }
                                buffer1.erase(buffer1.begin());
                                dirty1.erase(tempFrame);
                                buffer1.push_back(frameNum);
                                dirty1[frameNum] = dirty2[frameNum];

                                buffer2.erase(It2);
                                dirty2.erase(frameNum);
                                //push replaced buffer1 frame into the back of LRU table (buffer2)
                                buffer2.push_back(tempFrame);
                                dirty2[tempFrame] = tempRW;
                                break;
                        }
                        break;
                    }    
            }
        }
        std::cout << "Total memory frames: " << nframes << std::endl;
        std::cout << "Events in trace: " << count << std::endl;
        std::cout << "Total disk reads: " << diskReads << std::endl;
        std::cout << "Total disk writes: " << diskWrites << std::endl;

        fclose(tracefile);
    }
}