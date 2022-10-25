#include "dataStructures.hpp"
#include "policies.hpp"


//Function for FIFO Algorithm 
void FIFO(int nframes, char* traceName, char *debugOrQuiet){
    //use a different class for each page table object based on what the replacement algorithm needs
    CircularArray pageTable(nframes); //passed as argument
    //std::cout << pageTable.array[0].first << std::endl;
    FILE *tracefile;
    tracefile = fopen(traceName, "r"); //argv[0] = <tracefile>
    
    unsigned addr; 
    unsigned frameNum;
    char rw;
    int hits = 0;
    int count = 0;
    int reads = 0;
    int writes = 0;
    int offset = 0;
    int replacementIndex = 0;

    std::vector<int>::iterator it;
    std::vector<int> pgtble;
    std::map<int, char> dirty;


    while (fscanf(tracefile,"%x %c",&addr,&rw) != EOF) //Loop: read each address from trace file
    {
        count++;
        //std::cout << "Line count: " << count << "\n";
        frameNum = addr / 4096; //Extract frame number by removing the 12 offset bits
        //std::cout << "Frame Number: " << frameNum << " ";

        it = find(pgtble.begin(), pgtble.end(), frameNum);
        if (it==pgtble.end()) { //If the frame is not found in the page table
            if (dirty.size() < nframes){  //If page table is not full
                reads++;
                if(strcmp(debugOrQuiet, "debug") == 0){
                    std::cout<<"Table is not full, adding frame to the table\n";
                }
                pgtble.push_back(frameNum);
                dirty[frameNum] = rw;
            }
            else{   //table is full
                if(strcmp(debugOrQuiet, "debug") == 0){
                    std::cout << "Table is full and page wasn't found, replacing the oldest entry\n";
                }
                
                reads++;

                if (dirty[frameNum] == 'W') {
                    writes++;
                }

                pgtble.erase(pgtble.begin());
                dirty.erase(frameNum);
                pgtble.push_back(frameNum);
                dirty[frameNum] = rw;
                replacementIndex++;
                
            }
        }
        else{   //frame is in page table
            if(strcmp(debugOrQuiet, "debug") == 0){
                std::cout<<"Frame is in page table\n";
            }
            if((dirty[frameNum] != 'W') && (rw == 'W')){
                dirty[frameNum] = rw;
            }
            hits++;
        }




        // //loop to compare addr to each page table entry
        // for (int i = 0; i < pageTable.getSize(); i++) {
        //     //std::cout << "Page Table entry: " << pageTable.array[i].first << "\n";
        //     if (pageTable.array[i].first == 0)//Check if page table is empty
        //     {
        //         reads++;
        //         pageTable.array[i].first = frameNum;
        //         if (rw == 'W'){
        //             pageTable.array[i].second = 'W';
        //         }

        //         if(strcmp(debugOrQuiet, "debug") == 0){
        //             std::cout<<"Table entry " << i << " is empty, adding frame to the table\n";
        //         }
        //         break;
        //     }
        //     else if (frameNum == pageTable.array[i].first)//If frame number is found in page table
        //     {
        //         hits++;
        //         if (rw == 'W')
        //         {
        //             pageTable.array[i].second = rw;
        //         }
        //         // if (rw == 'R')
        //         // {
        //         //     reads++;
        //         // }
        //         if(strcmp(debugOrQuiet, "debug") == 0){
        //             std::cout<<"Frame is in page table\n";
        //         }
        //         //std::cout << "First if statement @ count " << count << ". Break"<<std::endl;
        //         break;
        //     }
        //     //if the element isn't in the page table, the table isn't empty, and it is at the last element at the page table. 
        //     else if (i == (pageTable.getSize()-1)){
        //         if (pageTable.array[i].second == 'W') {
        //             writes++;
        //             pageTable.array[i].second = 'R';
        //         }
        //         if(strcmp(debugOrQuiet, "debug") == 0){
        //             std::cout << "Table is full and page wasn't found, replacing the oldest entry\n";
        //         }
        //         int replacementIndex = pageTable.calculateCircularIndex();
        //         //std::cout << "Index = " << replacementIndex << "\n";

        //         pageTable.array[replacementIndex].first = frameNum;
        //         //std::cout << "array at index = " << pageTable.array[replacementIndex].first << "\n";
        //         pageTable.incrementLoopOffset();
        //         // if (pageTable.array[replacementIndex].second == 'W')
        //         // {
        //         //     writes++;
        //         // }
        //         // else if (rw == 'R')
        //         // {
        //         //     reads++;
        //         // }
        //         reads++;
        //         pageTable.array[replacementIndex].second = rw;
                
        //         //std::cout << "Replaced" << std::endl;
        //     }

            
        // }
        //std::cout<< "End of page table for loop" << std::endl;

    }
    // if (feof(tracefile)){
    //     std::cout << "End of File was reached" << std::endl;
    // }
    //std::cout << "Line count: " << count << "\n";
    //std::cout<<"test" << std::endl;

    //This is the replacement policy code if the page isn't found and it isn't empty

    // std::cout<< "Successfully added\n";
    // for (int i = 0; i < pageTable.getSize(); i++) {
    //     std::cout << pageTable.array[i].first << ", ";
    // }
    // std::cout << "Hits: " << hits << "\n";
    // std::cout << "Reads: " << reads << "\n";
    // std::cout << "Writes: " << writes << "\n";

    //std::cout << size << std::endl;



    std::cout << "Total memory frames: " << nframes << std::endl;
    std::cout << "Events in trace: " << count << std::endl;
    std::cout << "Total disk reads: " << reads << std::endl;
    std::cout << "Total disk writes: " << writes << std::endl;

    fclose(tracefile); //argv[0] = <tracefile>
    //std::cout << "end" << std::endl;
}


// int main(){
//     //int frames[7] = {0x0042bf60, 0x2f293f60, 0x1f16ff60, 0x0041f760, 0x37c1f760, 0x0041f840, 0x0041f860};
//     FIFO(64, "bzip.trace");

//     return 0;
// }