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
    //Dont set direction if user wants opposed direction
    if((dir == LEFT && direction == RIGHT) || (dir == RIGHT && direction == LEFT))
        return;
    
    if((dir == UP && direction == DOWN) || (dir == DOWN && direction == UP))
        return;
    
    direction = dir;
}

//Return false if movement fails (eg. collision)
bool Snake::moveSnake()
{
    int oldX, oldY;
    oldX = snakeX;
    oldY = snakeY;
    
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
    {
        if(snakeX >= maxX || snakeX < 1 || snakeY >= maxY || snakeY < 1)
            return false;
    }
    else
    {
        if(snakeX >= maxX)
            snakeX = 1;
        
        if(snakeX < 1)
            snakeX = maxX-1;
        
        if(snakeY >= maxY)
            snakeY = 1;
        
        if(snakeY < 1)
            snakeY = maxY-1;
    }
    
    //False when snake eat own body
    for(unsigned int i = 0; i < snakeBody.size(); i++)
        if(snakeX == snakeBody[i].getX() && snakeY == snakeBody[i].getOldY())
            return false;
        
    snakeHead.setPosition(Vector2f(snakeX*snakeSize, snakeY*snakeSize)); 
    
    snakeBody[0].setNewPosition(oldX, oldY);
    
    //If there are more elements than 1, move them all
    if(snakeBody.size() > 1)
        for(unsigned int i = 1; i < snakeBody.size(); i++)
            snakeBody[i].setNewPosition(snakeBody[i-1].getOldX(), snakeBody[i-1].getOldY());
    
    return true;
}

void Snake::addSegment(int x, int y)
{
    DoubleVector2 vec(snakeX, snakeY);
    snakeBody.insert(snakeBody.begin(), vec);
    
    snakeX = x;
    snakeY = y;
}
