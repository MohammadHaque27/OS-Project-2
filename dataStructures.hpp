#ifndef D_STRUCTS
#define D_STRUCTS

#include <cstdlib>
#include <string>
#include <vector>
#include <utility>

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
    int loopOffset; // for loopOffset % size
};

//Right now, the stl vector using std::pair<unsigned, char> as elements will suffice as the LRU data structure
// class LRUQueue
// {
// public:
//     LRUQueue();

// private:

// };

#endif // D_STRUCTS
