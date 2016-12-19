#ifndef DOUBLEVECTOR2_H
#define DOUBLEVECTOR2_H

//This class contains double Vector 2. It contains 2D vector and saves old vector after change.
class DoubleVector2
{
private:
    int actualX, actualY, oldX, oldY;
    
public:
    DoubleVector2(int x, int y);
    void setNewPosition(int x, int y);
    
    int getX();
    int getY();
    int getOldX();
    int getOldY();
};

#endif // DOUBLEVECTOR2_H
