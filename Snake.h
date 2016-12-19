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
private:
    int snakeSize;
    int snakeX, snakeY; //Max 20 in X (800/40) and max 15 in Y (600/40)
    vector <DoubleVector2> snakeBody;
    
    RectangleShape snakeHead;
    RectangleShape snakeBodySegment;
    
public:
    Snake(int x, int y); //Create and put Snake in desired position
    void drawSnake(RenderWindow &window);
    int getX();
    int getY();

};

#endif // SNAKE_H
