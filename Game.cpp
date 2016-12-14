#include "Game.h"

Game::Game()
{
    renderWindow.create(sf::VideoMode(800,600), "SFML Snake");
    renderWindow.setVerticalSyncEnabled(true);
}

void Game::startGame()
{
    if(!font.loadFromFile("font/Xolonium-Bold.otf"))
    {
        std::cerr << "Failed to load font/Xolonium-Bold.otf!";
        return;
    }
    
    while(gameState != Game::ENDED)
    {
        renderWindow.clear();
        
        updateGame();
        
        renderWindow.display();
    }
}

void Game::updateGame()
{
    switch(gameState)
    {
        case Game::MENU:
            drawMenu();
        break;
        
        case Game::OPTIONS:
            drawOptions();
        break;
        
        case Game::PAUSED:
            pauseGame();
        break;
        
        case Game::STARTED:
            drawGame();
        break;
    }
}

void Game::drawMenu()
{
}

void Game::drawOptions()
{
}

void Game::pauseGame()
{
}

void Game::drawGame()
{
}
