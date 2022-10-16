#include "dataStructures.hpp"

CircularArray::CircularArray(int length)
{
    std::string array[length] = {nullptr};
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

int CircularArray::calculateCircularIndex(int index)
{
    return loopOffset % size;
}