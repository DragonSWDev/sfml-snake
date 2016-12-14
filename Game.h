#ifndef GAME_H
#define GAME_H

//C++ Headers
#include <iostream>
#include <ctime>
#include <cstdlib>

//SFML Headers
#include <SFML/Graphics.hpp>

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
