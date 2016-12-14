#ifndef GAME_H
#define GAME_H

//C++ Headers
#include <iostream>

//SFML Headers
#include <SFML/Graphics.hpp>

class Game
{
private:
    enum GameState {STARTED,MENU,OPTIONS,PAUSED,ENDED};
    GameState gameState;
    sf::RenderWindow renderWindow;
    sf::Font font;
    
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
