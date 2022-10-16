#include "dataStructures.hpp"

CircularArray::CircularArray(int length)
{
    array = (unsigned*) malloc(length);
    size = length;
    loopOffset = 0;
}

int CircularArray::getSize()
{
    return size;
}

int CircularArray::getLoopOffset()
{
    return loopOffset;
}
    
void CircularArray::incrementLoopOffset()
{
    loopOffset++;
}

int CircularArray::calculateCircularIndex()
{
    return loopOffset % size;
}

