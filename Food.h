#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>

#include <SFML/Graphics.hpp>

using namespace sf;

//Generate food for snake
class Food
{
private:
    int foodX, foodY;
    int foodSize;
    int screenWidth, screenHeight;
    RectangleShape foodShape;
    
public:
    Food(int width, int height, int size);
    void generateNewFood();
    int getFoodX();
    int getFoodY();
    void drawFood(RenderWindow &window);
};

#endif // FOOD_H
