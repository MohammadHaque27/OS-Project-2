#ifndef D_STRUCTS
#define D_STRUCTS

#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <iostream>
#include <queue>

class CircularArray 
{
public:    
    CircularArray(int length);
    int getSize();
    int getLoopOffset();
    void incrementLoopOffset();
    int calculateCircularIndex(); //used when index >= size
    std::pair<unsigned, char> *array; //may need to add array as a member somewhere, but also might not want it to be a private member

private:
    int size; //length of array
    unsigned loopOffset; // for loopOffset % size
};

#endif // D_STRUCTS
