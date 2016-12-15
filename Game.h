#ifndef GAME_H
#define GAME_H

//C++ Headers
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

//SFML Headers
#include <SFML/Graphics.hpp>

//Game headers
#include "Snake.h"

//Define
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

//Namespaces
using namespace std;
using namespace sf;

class Game
{
private:
    enum GameState {STARTED,MENU,OPTIONS,PAUSED,ENDED};
    GameState gameState;
    RenderWindow renderWindow;
    
    Font font;
    
    Text gameName;
    Text menuStrings[3];
    Text optionsStrings[7];
    Text snakePoints;
    Text gameTime;
    
    bool snakeFast;
    bool generateWalls;
    bool canWalkBorder;
    
    RectangleShape wallsCheckbox;
    RectangleShape borderCheckbox;
    RectangleShape gameBorder;
    
    int points;
    int playTime;
        
    string pointsText;
    string timeText;
    
    void updateGame();
    
    void drawMenu();
    void drawOptions();
    void drawGame();
    void pauseGame();
    
public:
    Game();
    void startGame();
};

#endif // GAME_H
