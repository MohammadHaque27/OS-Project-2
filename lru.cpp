
#include "policies.hpp"
#include "dataStructures.cpp"
#include <iostream>
#include <map>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <stdlib.h>


//Function for the LRU Algorithm
void lru(const char* tracefile , int frame_Num, string option)
{
    
    //use a different class for each page table object based on what the replacement algorithm needs
    LRUQueue pageTable(nframes);
    vector<int> It;
    vector<int> Pg_Table;
    map<int, char> = mem;

    unsigned int changes; // any changes in our event
    unsigned int read;
    unsigned int write;
    
    FILE * tracefile;
    tracefile = fopen(traceName, "r");
    
    unsigned addr;
    unsigned trace = 0; 
    char rw = ' ';
    while (fscanf(tracefile,"%x %c",&addr,&rw) != EOF)  //This the first loop
    {
        frameNum = addr / 4096; //Extract frame number by removing the 12 offset bits
        //loop to compare addr to each page table entry
        It = find(Pg_table.begin(), Pg_table.end(), trace); //finding the fameNum in the pg table 
        //check if address in page table 
            if(It == Pg_table.end())// loop for page misses
            {
                if(mem.size() < frame_Num)
                {
                    Pg_table.push_back(trace);
                    mem[trace] = rw;
                }

                if(strcmp(option.c_str(), "debug"))
                {
                    cout << "Miss" << endl //print out miss
                }

                read++;

                else
                {
                    if(mem[Pg_table.front()] == 'W')
                    {
                        write++;
                    }

                    mem.erase(Pg_table.front());
                    Pg_table.erase(Pg_table.begin());


                    mem[trace] = rw;
                    Pg_table.push_back(trace);

                }

            }
            else
            {
                if(strcmp(option.c_str(), "debug"))
                {
                    cout << "Hit" << endl  //print out hit
                }

                Pg_table.erase(It);
                Pg_table.push_back(trace);

                if(mem[trace] == "R")
                {
                    mem[trace] = rw;
                }
            } 
            changes++ //counter for dirty
    }
    fclose(tracefile);

    cout << "Total memory frames" << frame_Num << endl;
    cout << "Events in trace" << changes << endl;
    cout << "Total disk reads" << read << endl;
    cout << "Total disk writes" << write << endl;
}





/*
    // if the page is not in LRU and the LRU is full
    //pop the front of the array 
    //add the new page to the back
    int temp = frame_Num;
    array_object.erase(array_object.begin());
    for(int i = 0; i=<len(array_object); i++){
        array_object[i+1] = array_object[i]; // pushes each item 1 position to the left

    }
    array_object.push_back(temp);// adds the temp to the last postion of the array
    std:: << cout << array_object;
    */