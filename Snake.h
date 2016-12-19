#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "DoubleVector2.h"

#define SNAKE_SIZE 40 //Snake is reactangle

using namespace std;
using namespace sf;

class Snake
{
public:
    enum MoveDirection {UP, DOWN, LEFT, RIGHT};
    
    Snake(int x, int y, int width, int height, bool enableBorder); //Create and put Snake in desired position
    void drawSnake(RenderWindow &window);
    int getX();
    int getY();
    bool moveSnake();
    void setDirection(MoveDirection dir);
    
private:
    int snakeSize;
    int snakeX, snakeY; //Max 20 in X (800/40) and max 15 in Y (600/40)
    int maxX, maxY;
    int canWalkBorder;
    vector <DoubleVector2> snakeBody;
    
    RectangleShape snakeHead;
    RectangleShape snakeBodySegment;
    
    MoveDirection direction;

};

#endif // SNAKE_H
