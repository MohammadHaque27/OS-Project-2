#include "policies.hpp"
#include "dataStructures.cpp"
#include <iostream>
#include <map>
#include <algorithm>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <queue>
using namespace std;

//Function for the LRU Algorithm
//if the page is not in LRU and the LRU is full
//pop the front of the array 
//add the new page to the back

void lru(const char* traceName , int frame_Num, string option)
{
    //use a different class for each page table object based on what the replacement algorithm needs
    //LRUQueue pageTable(nframes);
    vector<int>::iterator It;
    vector<int> Pg_table;
    map<int, char> mem;

    unsigned int changes; //any changes in our event
    unsigned int Disk_reads;
    unsigned int Disk_writes;
    
    FILE * tracefile;
    tracefile = fopen(traceName, "r");
    
    unsigned addr;
    unsigned trace = 0; 
    char rw = ' ';
    int choice = 0;

    while (fscanf(tracefile,"%x %c",&addr,&rw) != EOF)  //This the first loop goes through the file 
    {
        trace = addr / 4096; //Extract frame number by removing the 12 offset bits
        //loop to compare addr to each page table entry
        It = find(Pg_table.begin(), Pg_table.end(), trace); //finding the trace in the pg table 
        //check if address in page table 
            if(It == Pg_table.end())// code to get page misses
            {
               choice = 1;
            }

            else
            {
                choice = 2;
            } 
            changes++; //counter for dirty

            switch(choice) 
            {
                case 1:
                  if(strcmp(option.c_str(), "quiet"))
                {
                    cout << "Miss" << endl; //print out miss
                }

                Disk_reads++;
                
                if(mem.size() < frame_Num)
                {
                    Pg_table.push_back(trace);
                    mem[trace] = rw;
                }

                else 
                {
                    if(mem[Pg_table.front()] == 'W')
                    {
                        Disk_writes++;
                    }

                    mem.erase(Pg_table.front());
                    Pg_table.erase(Pg_table.begin());


                    mem[trace] = rw;
                    Pg_table.push_back(trace);

                }
                  break;

                case 2:
                  if(strcmp(option.c_str(), "quiet"))
                {
                    cout << "Hit" << endl;  //print out hit
                }

                Pg_table.erase(It);
                Pg_table.push_back(trace);

                if(mem[trace] == 'R')
                {
                    mem[trace] = rw;
                }
                  break;
            }

    }
    fclose(tracefile);

    cout << "Total memory frames: " << frame_Num << endl;
    cout << "Events in trace: " << changes << endl;
    cout << "Total disk reads: " << Disk_reads << endl;
    cout << "Total disk writes: " << Disk_writes << endl;
}


int main(){
    
    lru("bzip.trace", 64, "quiet");

    return 0;
}


/*
    int temp = frame_Num;
    array_object.erase(array_object.begin());
    for(int i = 0; i=<len(array_object); i++){
        array_object[i+1] = array_object[i]; // pushes each item 1 position to the left

    }
    array_object.push_back(temp);// adds the temp to the last postion of the array
    std:: << cout << array_object;
    */