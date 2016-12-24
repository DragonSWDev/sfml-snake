#ifndef WALL_H
#define WALL_H

#include <vector>
#include <cstdlib>

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Wall
{
private:
    vector <Vector2f> parts;
    RectangleShape wall;
    int wallSize;
    
public:
    Wall(int size, int width, int height);
    bool isCollision(int x, int y);
    void drawWall(RenderWindow &window);
};

#endif // WALL_H
