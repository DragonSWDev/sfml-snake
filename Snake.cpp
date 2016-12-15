#include "Snake.h"

Snake::Snake(int x, int y)
{
    snakeSize = SNAKE_SIZE;
    
    snakeHead.setSize(Vector2f(snakeSize,snakeSize));
    snakeHead.setFillColor(Color::Green);
    
    snakeX = x;
    snakeY = y;
    
    snakeHead.setPosition(snakeX*40,snakeY*40);
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
    window.draw(snakeHead);
}

