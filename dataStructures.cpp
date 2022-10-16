#include "dataStructures.hpp"

CircularArray::CircularArray(int length)
{
    std::string new array[length] = {nullptr};
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