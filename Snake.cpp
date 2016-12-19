#include "Snake.h"

Snake::Snake(int x, int y, int width, int height, bool enableBorder)
{
    maxX = width/SNAKE_SIZE-1;
    maxY = height/SNAKE_SIZE-1;
    canWalkBorder = enableBorder;
    
    snakeSize = SNAKE_SIZE;
    
    snakeHead.setSize(Vector2f(snakeSize,snakeSize));
    snakeHead.setFillColor(Color::Green);
    
    snakeBodySegment.setSize(Vector2f(snakeSize, snakeSize));
    snakeBodySegment.setFillColor(Color::Yellow);
    
    snakeX = x;
    snakeY = y;
    
    snakeHead.setPosition(snakeX*snakeSize,snakeY*snakeSize);
    
    snakeBody.push_back(DoubleVector2(x, y+1)); //Add one body segment behind head
    
    direction = UP;
}

int Snake::getX()
{
    return snakeX;
}

int Snake::getY()
{
    return snakeY;
}

void Snake::drawSnake(RenderWindow& window)
{
    for(vector<DoubleVector2>::iterator i = snakeBody.begin(); i != snakeBody.end(); i++)
    {
        snakeBodySegment.setPosition(i->getX()*snakeSize, i->getY()*snakeSize);
        window.draw(snakeBodySegment);
    }
        
    
    window.draw(snakeHead);
}

void Snake::setDirection(Snake::MoveDirection dir)
{
    direction = dir;
}

//Return false if movement fails (eg. collision)
bool Snake::moveSnake()
{
    switch(direction)
    {
        case Snake::UP:
            snakeY--;
        break;
        
        case Snake::DOWN:
            snakeY++;
        break;
        
        case Snake::LEFT:
            snakeX--;
        break;
        
        case Snake::RIGHT:
            snakeX++;
        break;
    }
    
    if(!canWalkBorder)
        if(snakeX >= maxX || snakeY >= maxY)
            return false;
    
    return true;
}
