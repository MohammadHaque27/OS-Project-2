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
    std::vector<std::pair<unsigned, char> > buffer2;
    buffer2.reserve(size2);
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
                //...loop through LRU table
                if(strcmp(debugOrQuiet, "debug") == 0){
                    std::cout<< count <<": Buffer1 is full with no matches, begin searching buffer2" << std::endl;
                }
                for (int j = 0; j < size2; j++)
                {
                    if (frameNum == buffer2[j].first) //If entry is in LRU table
                    {
                        if(strcmp(debugOrQuiet, "debug") == 0){
                            std::cout<< count <<": Buffer2 entry " << j << " is a match, moving this entry to buffer1" << std::endl;
                        }
                        int replacementIndex = buffer1.calculateCircularIndex();
                        // if (buffer1.array[replacementIndex].second == 'W')
                        // {
                        //     diskWrites++;
                        // }
                        unsigned tempFrame = buffer1.array[replacementIndex].first;
                        char tempRW = buffer1.array[replacementIndex].second;
                        buffer1.array[replacementIndex].first = frameNum; //may need to move buffer1.array[replacementIndex] into buffer2 via a temp variable
                        buffer1.incrementLoopOffset();
                        buffer1.array[replacementIndex].second = rw;
                        // if (rw == 'R')
                        // {
                        //     diskReads++;
                        // }
                        buffer2.erase(buffer2.begin()+j);
                        std::pair<unsigned, char> elem;
                        elem.first = tempFrame;
                        elem.second = tempRW;
                        buffer2.push_back(elem);
                        break;
                    }
                    else if (buffer2[j].first == 0) //If entry not in LRU and at LRU index is empty
                    {
                        if(strcmp(debugOrQuiet, "debug") == 0){
                            std::cout<< count <<": Buffer2 entry " << j << " is empty, adding frame to the table" << std::endl;
                        }
                        buffer2[j].first = frameNum;
                        buffer2[j].second = rw;
                        if (rw == 'R')
                        {
                            diskReads++;
                            if(strcmp(debugOrQuiet, "debug") == 0){
                                std::cout<< count <<": Disk Read" << std::endl;
                            }
                        }
                        break;
                    }
                    else if (j < (size2-1)) //LRU table not full
                    {
                        continue;
                    }
                    else //Not in LRU Table and LRU Table is full
                    {
                        //add code here for adding to buffer1, moving replacement index from buffer 1 to buffer 2, and removing least recently used element from buffer 2.
                        if(strcmp(debugOrQuiet, "debug") == 0){
                            std::cout<< count <<": Buffer2 is full with no matches, adding frame to buffer1 and shifting buffer1 replacement to buffer2" << std::endl;
                        }
                        int replacementIndex = buffer1.calculateCircularIndex();
                        // if (buffer1.array[replacementIndex].second == 'W')
                        // {
                        //     diskWrites++;
                        // }
                        unsigned tempFrame = buffer1.array[replacementIndex].first;
                        char tempRW = buffer1.array[replacementIndex].second;
                        buffer1.array[replacementIndex].first = frameNum;
                        buffer1.incrementLoopOffset();
                        buffer1.array[replacementIndex].second = rw;
                        if (rw == 'R')
                        {
                            diskReads++;
                            if(strcmp(debugOrQuiet, "debug") == 0){
                                std::cout<< count <<": Disk Read" << std::endl;
                            }
                        }
                        if (buffer2.begin()->second == 'W') //new
                        {
                            diskWrites++;
                        }
                        buffer2.erase(buffer2.begin()); //erase least recently used (front vector queue element)
                        std::pair<unsigned, char> elem;
                        elem.first = tempFrame;
                        elem.second = tempRW;
                        buffer2.push_back(elem);
                        break;
                    }
                }

                // int replacementIndex = pageTable.calculateCircularIndex();
                // pageTable.array[replacementIndex] = frameNum;
                // pageTable.incrementLoopOffset();
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