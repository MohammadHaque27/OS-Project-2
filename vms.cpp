#include "policies.hpp"
#include "dataStructures.hpp"


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
        for (int i = 0; i < buffer1.getSize(); i++) {
            if (frameNum == buffer1.array[i].first)
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
            else if (buffer1.array[i].first == 0)//Check if page table index is empty
            {
                buffer1.array[i].first = frameNum;
                buffer1.array[i].second = rw;
                break;
            }
            else //needs to be added to the table
            {
                // int replacementIndex = pageTable.calculateCircularIndex();
                // pageTable.array[replacementIndex] = frameNum;
                // pageTable.incrementLoopOffset();
                break;
            }
        }

    }





    fclose(tracefile);
}