#include "policies.hpp"
#include "dataStructures.hpp" 
#include "dataStructures.cpp" 


void VMS(const char* traceName, int nframes, int p)
{
    int size2 = (nframes * p) / 100;
    int size1 = nframes - size2;

    //conditional to just run fifo or lru (figure out percentages)
    //if (size1 == 0)

    CircularArray buffer1(size1);
    std::vector<std::pair<unsigned, char>> buffer2;
    buffer2.reserve(size2);
    int bufferHits = 0;
    int diskReads = 0;
    int diskWrites = 0;

    FILE * tracefile;
    tracefile = fopen(traceName, "r");
    
    unsigned addr; 
    unsigned frameNum;
    char rw;
    //loop over each memory address in trace file
    while (fscanf(tracefile,"%x %c",&addr,&rw) != EOF)
    {
        frameNum = addr / 4096; //Extract frame number by removing the 12 offset bits
        //loop to compare frameNum to each page table entry
        for (int i = 0; i < size1; i++) 
        {
            if (frameNum == buffer1.array[i].first) //If entry is in FIFO table
            {
                bufferHits++;
                if ((buffer1.array[i].second != 'W') && (rw == 'W'))
                {
                    buffer1.array[i].second = rw;
                }
                if (rw == 'R')
                {
                    diskReads++;
                }
                break;
            }
            else if (buffer1.array[i].first == 0)//If entry not in FIFO table but FIFO table entry is empty
            {
                buffer1.array[i].first = frameNum;
                buffer1.array[i].second = rw;
                if (rw == 'R')
                {
                    diskReads++;
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
                for (int j = 0; j < size2; j++)
                {
                    if (frameNum == buffer2[j].first) //If entry is in LRU table
                    {
                        int replacementIndex = buffer1.calculateCircularIndex();
                        buffer1.array[replacementIndex].first = frameNum; //may need to move buffer1.array[replacementIndex] into buffer2 via a temp variable
                        buffer1.incrementLoopOffset();
                        if (buffer1.array[replacementIndex].second == 'W')
                        {
                            diskWrites++;
                        }
                        buffer1.array[replacementIndex].second = rw;
                        if (rw == 'R')
                        {
                            diskReads++;
                        }
                        buffer2.erase(buffer2.begin()+j);
                        break;
                    }
                    else if (buffer2[j].first = 0) //If entry at LRU index is empty
                    {
                        buffer2[j].first = frameNum;
                        buffer2[j].second = rw;
                        if (rw == 'R')
                        {
                            diskReads++;
                        }
                        break;
                    }
                }

                break;
            }
        }

    }





    //fclose(tracefile);
}