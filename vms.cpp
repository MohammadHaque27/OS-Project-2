#include "policies.hpp"
#include "dataStructures.hpp" 


void VMS(char* traceName, int nframes, int p, char *debugOrQuiet)
{
    int size2 = (nframes * p) / 100;
    int size1 = nframes - size2;

    //conditional to just run fifo or lru (figure out percentages)
    if (size1 == 0)
    {
        lru(traceName, nframes, debugOrQuiet);
    }

    if (size2 == 0)
    {
        FIFO(nframes, traceName, debugOrQuiet);
    }

    CircularArray buffer1(size1);
    std::vector<int>::iterator It;
    std::vector<int> buffer2;
    std::map<int, char> mem;
    //buffer2.reserve(size2);
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
        for (int i = 0; i < size1; i++) 
        {
            if (frameNum == buffer1.array[i].first) //If entry is in FIFO table
            {
                if(strcmp(debugOrQuiet, "debug") == 0){
                    std::cout<< count <<": Buffer1 entry " << i << " is a match" << std::endl;
                }
                //bufferHits++;
                if ((buffer1.array[i].second != 'W') && (rw == 'W'))
                {
                    buffer1.array[i].second = rw;
                }
                // if (rw == 'R')
                // {
                //     diskReads++;
                // }
                break;
            }
            else if (buffer1.array[i].first == 0)//If entry not in FIFO table but FIFO table entry is empty
            {
                if(strcmp(debugOrQuiet, "debug") == 0){
                    std::cout<< count <<": Buffer1 entry " << i << " is empty, adding frame to the table" << std::endl;
                }
                buffer1.array[i].first = frameNum;
                buffer1.array[i].second = rw;
                if (rw == 'R')
                {
                    diskReads++;
                    if(strcmp(debugOrQuiet, "debug") == 0){
                        std::cout<< count <<": Disk Read" << std::endl;
                    }
                }
                break;
            }
            else if (i < (size1-1)) //Table not full
            {
                continue;
            }
            else //If entry is not in FIFO table and FIFO is full...
            {
                //...search through LRU table
                if(strcmp(debugOrQuiet, "debug") == 0){
                    std::cout<< count <<": Buffer1 is full with no matches, begin searching buffer2" << std::endl;
                }
                int code;
                It = find(buffer2.begin(), buffer2.end(), frameNum); //Look for a frameNum match
                if(It == buffer2.end()) //set switch code for frame not in LRU table
                {
                    code = 1;  
                }
                else  //set switch code for frame in LRU table
                {
                    code = 2;
                } 
                
                switch(code) 
                {
                    case 1: //frame not in LRU table
                        diskReads++;
                        if(strcmp(debugOrQuiet, "debug") == 0){
                                std::cout<< count <<": Disk Read" << std::endl;
                            }
                        // if (rw == 'R')
                        // {
                        //     diskReads++;
                        //     if(strcmp(debugOrQuiet, "debug") == 0){
                        //         std::cout<< count <<": Disk Read" << std::endl;
                        //     }
                        // }
                        if(mem.size() < size2) //if LRU table not full
                        {
                            if(strcmp(debugOrQuiet, "debug") == 0){
                                std::cout<< count <<": Buffer2 entry is empty, adding frame to the table" << std::endl;
                            }
                            buffer2.push_back(frameNum);
                            mem[frameNum] = rw;
                        }
                        else //LRU table is full
                        {
                            if(strcmp(debugOrQuiet, "debug") == 0){
                                std::cout<< count <<": Buffer2 is full with no matches, adding frame to buffer1 and shifting buffer1 replacement to buffer2" << std::endl;
                            }
                            int replacementIndex = buffer1.calculateCircularIndex();
                            unsigned tempFrame = buffer1.array[replacementIndex].first;
                            char tempRW = buffer1.array[replacementIndex].second;

                            buffer1.array[replacementIndex].first = frameNum;
                            buffer1.array[replacementIndex].second = rw;
                            buffer1.incrementLoopOffset();
                            
                            if(mem[buffer2.front()] == 'W')
                            {
                                diskWrites++;
                            }
                            mem.erase(buffer2.front());
                            buffer2.erase(buffer2.begin());
                            //push replaced buffer1 frame into the back of LRU table (buffer2)
                            buffer2.push_back(tempFrame);
                            mem[tempFrame] = tempRW;
                        }
                        break;

                    case 2: //frame is in LRU table
                        if(strcmp(debugOrQuiet, "debug") == 0){
                            std::cout<< count <<": Buffer2 entry is a match, moving this entry to buffer1" << std::endl;
                        }
                        int replacementIndex = buffer1.calculateCircularIndex();
                        unsigned tempFrame = buffer1.array[replacementIndex].first;
                        char tempRW = buffer1.array[replacementIndex].second;
                        
                        if((mem[frameNum] != 'W') && (rw == 'W'))   
                        {
                            mem[frameNum] = rw;
                        }
                        buffer1.array[replacementIndex].first = frameNum;
                        buffer1.array[replacementIndex].second = mem[frameNum];
                        buffer1.incrementLoopOffset();
                        buffer2.erase(It);
                        mem.erase(frameNum);
                        //push replaced buffer1 frame into the back of LRU table (buffer2)
                        buffer2.push_back(tempFrame);
                        mem[tempFrame] = tempRW;
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