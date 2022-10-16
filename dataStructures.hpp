#ifndef D_STRUCTS
#define D_STRUCTS

#include <cstdlib>
#include <string>

class CircularArray 
{
public:    
    CircularArray(int length);
    int getSize();
    int getLoopOffset();
    void incrementLoopOffset();
    int calculateCircularIndex(); //used when index >= size

private:
<<<<<<< Updated upstream
    //std::string *array;
=======
    std::string *array;
>>>>>>> Stashed changes
    int size; //length of array
    int loopOffset; // for loopOffset % size
};

#endif // D_STRUCTS
