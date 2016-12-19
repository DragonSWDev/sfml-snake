#include "DoubleVector2.h"

DoubleVector2::DoubleVector2(int x, int y)
{
    actualX = x;
    actualY = y;
    
    oldX = 0;
    oldY = 0;
}

void DoubleVector2::setNewPosition(int x, int y)
{
    oldX = actualX;
    oldY = actualY;
    
    actualX = x;
    actualY = y;
}

int DoubleVector2::getOldX()
{
    return oldX;
}

int DoubleVector2::getOldY()
{
    return oldY;
}

int DoubleVector2::getX()
{
    return actualX;
}

int DoubleVector2::getY()
{
    return actualY;
}
