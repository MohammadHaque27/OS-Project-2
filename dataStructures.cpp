#include "dataStructures.hpp"

CircularArray::CircularArray(int length)
{
    size = length;
    std::string array[size] = {nullptr};
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