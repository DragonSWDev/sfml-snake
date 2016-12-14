#include "Game.h"

Game::Game()
{
    renderWindow.create(VideoMode(800,600), "SFML Snake");
    renderWindow.setVerticalSyncEnabled(true);
    
    gameState = MENU;
    
    srand(time(0));
}

void Game::startGame()
{
    if(!font.loadFromFile("font/Xolonium-Bold.otf"))
    {
        cerr << "Failed to load Xolonium-Bold.otf!";
        return;
    } 
        
    updateGame();
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
        
        case Game::ENDED:
            return;
        break;
    }
}

void Game::drawMenu()
{
    gameName.setFont(font);
    gameName.setString("SFML Snake");
    gameName.setCharacterSize(80);
    gameName.setPosition(SCREEN_WIDTH/2-gameName.getGlobalBounds().width/2,150);
    
    menuStrings[0].setFont(font);
    menuStrings[0].setString("Start Game");
    menuStrings[0].setCharacterSize(40);
    menuStrings[0].setPosition(SCREEN_WIDTH/2-menuStrings[0].getGlobalBounds().width/2,250);
    
    menuStrings[1].setFont(font);
    menuStrings[1].setString("Options");
    menuStrings[1].setCharacterSize(40);
    menuStrings[1].setPosition(SCREEN_WIDTH/2-menuStrings[1].getGlobalBounds().width/2,300);
    
    menuStrings[2].setFont(font);
    menuStrings[2].setString("Exit");
    menuStrings[2].setCharacterSize(40);
    menuStrings[2].setPosition(SCREEN_WIDTH/2-menuStrings[2].getGlobalBounds().width/2,350);
    
    Event event;
    Vector2f mouse();
    
    while(gameState == Game::MENU)
    {
        Vector2f mouse(Mouse::getPosition(renderWindow));
        
        while(renderWindow.pollEvent(event))
        {
            if(event.type == Event::Closed)
                gameState = ENDED;
            
            if(event.type == Event::MouseButtonReleased)
            {
                if(menuStrings[0].getGlobalBounds().contains(mouse) && event.mouseButton.button == Mouse::Left)
                    gameState = STARTED;
                
                if(menuStrings[1].getGlobalBounds().contains(mouse) && event.mouseButton.button == Mouse::Left)
                    gameState = OPTIONS;
                
                if(menuStrings[2].getGlobalBounds().contains(mouse) && event.mouseButton.button == Mouse::Left) 
                    gameState = ENDED;
                
            }
        }
        
        renderWindow.clear();
        
        renderWindow.draw(gameName);
        
        for(int i = 0; i < 3; i++)
            renderWindow.draw(menuStrings[i]);
        
        for(int i = 0; i < 3; i++)
            if(menuStrings[i].getGlobalBounds().contains(mouse))
                menuStrings[i].setFillColor(Color::Green);
            else
                menuStrings[i].setFillColor(Color::White);
            
        
        renderWindow.display();
    }
    
    updateGame();
}

void Game::drawOptions()
{
    updateGame();
}

void Game::pauseGame()
{
    updateGame();
}

void Game::drawGame()
{
    updateGame();
}
