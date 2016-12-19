#include "Snake.h"

Snake::Snake(int x, int y)
{
    snakeSize = SNAKE_SIZE;
    
    snakeHead.setSize(Vector2f(snakeSize,snakeSize));
    snakeHead.setFillColor(Color::Green);
    
    snakeBodySegment.setSize(Vector2f(snakeSize, snakeSize));
    snakeBodySegment.setFillColor(Color::Yellow);
    
    snakeX = x;
    snakeY = y;
    
    snakeHead.setPosition(snakeX*snakeSize,snakeY*snakeSize);
    
    snakeBody.push_back(DoubleVector2(x, y+1)); //Add one body segment behind head
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

