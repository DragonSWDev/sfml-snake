#include "Food.h"

Food::Food(int width, int height, int size)
{
    screenWidth = width;
    screenHeight = height;
    foodSize = size;
    
    //Rand <SIZE, WIDTH|HEIGHT - SIZE> to fit in game border
    foodX = rand()%(screenWidth/size - 2) + 1;
    foodY = rand()%(screenHeight/size - 2) + 1;
    
    foodShape.setSize(Vector2f(size,size));
    foodShape.setFillColor(Color::Red);
    foodShape.setPosition(foodX*size, foodY*size);
}

void Food::generateNewFood()
{
    foodX = rand()%(screenWidth/foodSize - 2) + 1;
    foodY = rand()%(screenHeight/foodSize - 2) + 1;
    
    foodShape.setPosition(foodX*foodSize, foodY*foodSize);
}

int Food::getFoodX()
{
    return foodX;
}

int Food::getFoodY()
{
    return foodY;
}

void Food::drawFood(sf::RenderWindow& window)
{
    window.draw(foodShape);
}
