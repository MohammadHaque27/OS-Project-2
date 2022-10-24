#include "policies.hpp"
#include "dataStructures.hpp"

//Function for the LRU Algorithm
//if the page is not in LRU and the LRU is full
//pop the front of the array 
//add the new page to the back

void lru(const char* traceName , int frame_Num, std::string option)
{

    
    unsigned int count = 0; 
    // disk reads
    unsigned int Disk_reads = 0; 
    // disk writes   
    unsigned int Disk_writes = 0;

    //use a different class for each page table object based on what the replacement algorithm needs
    std::vector<int>::iterator It;
    std::vector<int> Pg_table;
    std::map<int, char> mem;
    
    //opening the tracefile that we are reading from
    FILE * tracefile;
    
    tracefile = fopen(traceName, "r");
    
    unsigned addr;
    unsigned trace = 0; 
    char rw = ' ';
    int choice = 0;
    //int Hits = 0;

    while (fscanf(tracefile,"%x %c",&addr,&rw) != EOF)  //This the first loop goes through the file 
    {
        trace = addr / 4096; //Extract frame number by removing the 12 offset bits
        //loop to compare addr to each page table entry
        It = find(Pg_table.begin(), Pg_table.end(), trace); //finding the trace in the pg table 
        
            if(It == Pg_table.end())// code to get page misses
            {
               choice = 1;  
            }

            else  // code to get hits
            {
                choice = 2;
            } 
            count++; 

            switch(choice) 
            {
                case 1:
                  if(strcmp(option.c_str(), "quiet")) //if choosen option is 'quiet'
                {
                    std::cout << "Miss" << std::endl; //print out miss
                }

                Disk_reads++;  //increment read
                
                if(mem.size() < frame_Num)
                {
                    Pg_table.push_back(trace);
                    mem[trace] = rw;
                }

                else 
                {
                    if(mem[Pg_table.front()] != 'R')  //if 'W'
                    {
                        Disk_writes++;  // increment write
                    }

                    mem.erase(Pg_table.front());
                    mem[trace] = rw;
                    Pg_table.erase(Pg_table.begin());
                    // push trace into page table from back
                    Pg_table.push_back(trace);   

                }
                  break;

                case 2:
                  if(strcmp(option.c_str(), "quiet"))  //if choosen option is 'quiet'
                {
                    std::cout << "Hit" << std::endl;  //print out hit
                    //Hits++;
                }

                Pg_table.erase(It);

                // push trace into page table from back
                Pg_table.push_back(trace);

                if(mem[trace] != 'W')   
                {
                    mem[trace] = rw;
                }
                  break;
            }

    }
    fclose(tracefile);   //close trace file 

    //output for lru
    std::cout << "Total memory frames: " << frame_Num << std::endl;
    std::cout << "Events in trace: " << count << std::endl;
    std::cout << "Total disk reads: " << Disk_reads << std::endl;
    std::cout << "Total disk writes: " << Disk_writes << std::endl;
    
}

/*
int main(){
    
    lru("sixpack.trace", 4, "debug");

    return 0;
}
*/
