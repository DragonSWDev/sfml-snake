#include "Game.h"

Game::Game()
{
    renderWindow.create(VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "SFML Snake");
    renderWindow.setVerticalSyncEnabled(true);
    
    gameState = MENU;
    
    srand(time(0));
    
    snakeFast = false;
    canWalkBorder = true;
    generateWalls = false;
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
    
    while(gameState == Game::MENU)
    {
        Vector2f mouse(Mouse::getPosition(renderWindow));
        
        while(renderWindow.pollEvent(event))
        {
            //Exit after clicking X on window
            if(event.type == Event::Closed)
                gameState = ENDED;
            
            //Go to game, options or exit when user selects option in menu
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
    optionsStrings[0].setString("OPTIONS");
    optionsStrings[1].setString("Snake speed");
    optionsStrings[2].setString("Can walk through border");
    optionsStrings[3].setString("Generate random walls");
    optionsStrings[4].setString("Back");
    optionsStrings[5].setString("Slow");
    optionsStrings[6].setString("Fast");
    
    optionsStrings[0].setFont(font);
    optionsStrings[0].setCharacterSize(80);
    optionsStrings[0].setPosition(SCREEN_WIDTH/2-optionsStrings[0].getGlobalBounds().width/2, 50);
    
    //Set 'Slow' string
    optionsStrings[5].setFont(font);
    optionsStrings[5].setCharacterSize(40);
    optionsStrings[5].setPosition(SCREEN_WIDTH/2-optionsStrings[1].getGlobalBounds().width/2-optionsStrings[5].getGlobalBounds().width, 240);
    
    //Set 'Fast' string
    optionsStrings[6].setFont(font);
    optionsStrings[6].setCharacterSize(40);
    optionsStrings[6].setPosition(SCREEN_WIDTH/2-optionsStrings[1].getGlobalBounds().width/2+20, 240);
    
    for(int i = 1; i < 5; i++)
    {
        optionsStrings[i].setFont(font);
        optionsStrings[i].setCharacterSize(40);
        
        optionsStrings[i].setPosition(SCREEN_WIDTH/2-optionsStrings[i].getGlobalBounds().width/2, 100+100*i);
    }
    
   Event event;
   
   while(gameState == Game::OPTIONS)
   {
      Vector2f mouse(Mouse::getPosition(renderWindow));
      
      while(renderWindow.pollEvent(event))
      {
          //Back to menu after selecting "Back" in options
          if(event.type == Event::MouseButtonReleased)
              if(optionsStrings[4].getGlobalBounds().contains(mouse) && event.mouseButton.button == Mouse::Left)
                gameState = MENU;
             
          //Back to menu when Escape pressed
          if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
              gameState = MENU;
          
          //Exit game after clicking X on window
          if(event.type == Event::Closed)
              gameState = ENDED;
          
          //Set slow snake speed after selecting it
          if(event.type == Event::MouseButtonReleased)
              if(optionsStrings[5].getGlobalBounds().contains(mouse) && event.mouseButton.button == Mouse::Left && snakeFast)
                snakeFast = false;
          
          ////Set fast snake speed after selecting it
          if(event.type == Event::MouseButtonReleased)
              if(optionsStrings[6].getGlobalBounds().contains(mouse) && event.mouseButton.button == Mouse::Left && !snakeFast)
                snakeFast = true;
              
      }
      
      if(optionsStrings[4].getGlobalBounds().contains(mouse)) //Change 'Back' string color to green on mouse hover
          optionsStrings[4].setFillColor(Color::Green);
      else
          optionsStrings[4].setFillColor(Color::White);
      
      //Highlight string on mouse hover when it is not choosen (yellow)
      if(optionsStrings[5].getGlobalBounds().contains(mouse) && snakeFast)
          optionsStrings[5].setFillColor(Color::Green);
      else
          optionsStrings[5].setFillColor(Color::White);
      
      //Same as before
      if(optionsStrings[6].getGlobalBounds().contains(mouse) && !snakeFast)
          optionsStrings[6].setFillColor(Color::Green);
      else
          optionsStrings[6].setFillColor(Color::White);
      
      //Highlight choosen option in Snake speed
      if(!snakeFast)
          optionsStrings[5].setFillColor(Color::Yellow);
      else
          optionsStrings[6].setFillColor(Color::Yellow);
      
      renderWindow.clear();
      
      for(int i = 0; i < 7; i++)
          renderWindow.draw(optionsStrings[i]);
      
      renderWindow.display();
   }

    
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
