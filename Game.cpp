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
    gamePaused = false;
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
        
        case Game::STARTED:
            drawGame();
        break;
        
        case Game::OVER:
            gameOver();
        break;
        
        case Game::ENDED:
            renderWindow.close();
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
    optionsStrings[3].setString("Generate random wall");
    optionsStrings[4].setString("Back");
    optionsStrings[5].setString("Slow");
    optionsStrings[6].setString("Fast");
    
    optionsStrings[0].setFont(font);
    optionsStrings[0].setCharacterSize(80);
    optionsStrings[0].setPosition(SCREEN_WIDTH/2-optionsStrings[0].getGlobalBounds().width/2, 50);
    
    //Draw strings
    for(int i = 1; i < 5; i++)
    {
        optionsStrings[i].setFont(font);
        optionsStrings[i].setCharacterSize(40);
        
        optionsStrings[i].setPosition(SCREEN_WIDTH/2-optionsStrings[i].getGlobalBounds().width/2, 100+100*i);
    }
    
    //Set 'Slow' string
    optionsStrings[5].setFont(font);
    optionsStrings[5].setCharacterSize(40);
    optionsStrings[5].setPosition(SCREEN_WIDTH/2-optionsStrings[5].getGlobalBounds().width, 240);
    
    //Set 'Fast' string
    optionsStrings[6].setFont(font);
    optionsStrings[6].setCharacterSize(40);
    optionsStrings[6].setPosition(SCREEN_WIDTH/2+optionsStrings[5].getGlobalBounds().width/4, 240);
    
    //Set checkboxes
    borderCheckbox.setSize(Vector2f(20,20));
    borderCheckbox.setOutlineColor(Color::Red);
    borderCheckbox.setFillColor(Color::Black);
    borderCheckbox.setOutlineThickness(5);
    borderCheckbox.setPosition(SCREEN_WIDTH/2, 350);
    
    wallsCheckbox.setSize(Vector2f(20,20));
    wallsCheckbox.setOutlineColor(Color::Red);
    wallsCheckbox.setFillColor(Color::Black);
    wallsCheckbox.setOutlineThickness(5);
    wallsCheckbox.setPosition(SCREEN_WIDTH/2, 450);
    
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
          
          //Set fast snake speed after selecting it
          if(event.type == Event::MouseButtonReleased)
              if(optionsStrings[6].getGlobalBounds().contains(mouse) && event.mouseButton.button == Mouse::Left && !snakeFast)
                snakeFast = true;
              
          //Set right flag after choosing checkbox
          if(event.type == Event::MouseButtonReleased)
              if(borderCheckbox.getGlobalBounds().contains(mouse))
              {
                  if(!canWalkBorder)
                    canWalkBorder = true;
                  else
                      canWalkBorder = false;
              }
                  
          if(event.type == Event::MouseButtonReleased)
              if(wallsCheckbox.getGlobalBounds().contains(mouse))
              {
                  if(!generateWalls)
                      generateWalls = true;
                  else
                      generateWalls = false;
              }
              
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
      
      
      //Mark or unmark checkbox
      if(canWalkBorder)
          borderCheckbox.setFillColor(Color::Yellow);
      else
          borderCheckbox.setFillColor(Color::Black);
      
      if(generateWalls)
          wallsCheckbox.setFillColor(Color::Yellow);
      else
          wallsCheckbox.setFillColor(Color::Black);
          
      
      renderWindow.clear();
      
      for(int i = 0; i < 7; i++)
          renderWindow.draw(optionsStrings[i]);
      
      renderWindow.draw(borderCheckbox);
      renderWindow.draw(wallsCheckbox);
      
      renderWindow.display();
   }

    
    updateGame();
}

void Game::gameOver()
{
    for(int i = 0; i < 4; i++)
    {
        gameOverStrings[i].setFont(font);
        gameOverStrings[i].setFillColor(Color::White);
    }
    
    //Game over string
    gameOverStrings[0].setString("Game Over!");
    gameOverStrings[0].setCharacterSize(80);
    gameOverStrings[0].setPosition(SCREEN_WIDTH/2-gameOverStrings[0].getGlobalBounds().width/2,150);
    gameOverStrings[0].setFillColor(Color::Red);
    
    ostringstream buffer;
    pointsText = "Your points: ";
    buffer << points;
    pointsText += buffer.str();
    gameOverStrings[1].setCharacterSize(40);
    gameOverStrings[1].setString(pointsText);
    gameOverStrings[1].setPosition(SCREEN_WIDTH/2-gameOverStrings[1].getGlobalBounds().width/2,240);
    
    //Clear buffer
    buffer.str("");
    buffer.clear();
    
    pointsText = "Your time: ";
    buffer << playTime;
    pointsText += buffer.str();
    pointsText += "s";
    gameOverStrings[2].setCharacterSize(40);
    gameOverStrings[2].setString(pointsText);
    gameOverStrings[2].setPosition(SCREEN_WIDTH/2-gameOverStrings[1].getGlobalBounds().width/2,280);
    
    buffer.str("");
    buffer.clear();
    
    gameOverStrings[3].setString("Back to menu");
    gameOverStrings[3].setCharacterSize(40);
    gameOverStrings[3].setPosition(SCREEN_WIDTH/2-gameOverStrings[3].getGlobalBounds().width/2,340);
    
    Event event;
    while(gameState == Game::OVER)
    {
        Vector2f mouse(Mouse::getPosition(renderWindow));
        
        while(renderWindow.pollEvent(event))
        {
            if(event.type == Event::Closed)
                gameState = ENDED;
            
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                gameState = MENU;
            
            if(event.type == Event::MouseButtonReleased)
                if(event.mouseButton.button == Mouse::Left && gameOverStrings[3].getGlobalBounds().contains(mouse))
                    gameState = MENU;
        }
        
        if(gameOverStrings[3].getGlobalBounds().contains(mouse))
            gameOverStrings[3].setFillColor(Color::Green);
        else
            gameOverStrings[3].setFillColor(Color::White);
        
        renderWindow.clear();
        
        for(int i = 0; i < 4; i++)
            renderWindow.draw(gameOverStrings[i]);
        
        renderWindow.display();
    }
    
    
    updateGame();
}

void Game::drawGame()
{
    Snake snake(SCREEN_WIDTH/2/SNAKE_SIZE, SCREEN_HEIGHT/2/SNAKE_SIZE, SCREEN_WIDTH, SCREEN_HEIGHT, canWalkBorder); //Create snake in center of the window
    Food food(SCREEN_WIDTH, SCREEN_HEIGHT, SNAKE_SIZE);
        
    //Draw border - it's a big reactangle with transparent fill
    gameBorder.setPosition(SNAKE_SIZE,SNAKE_SIZE);
    gameBorder.setSize(Vector2f(SCREEN_WIDTH-SNAKE_SIZE*2, SCREEN_HEIGHT-SNAKE_SIZE*2));
    gameBorder.setFillColor(Color::Black);
    gameBorder.setOutlineThickness(3);
    gameBorder.setOutlineColor(Color::Red);
    
    snakePoints.setFont(font);
    snakePoints.setCharacterSize(20);
    snakePoints.setPosition(SNAKE_SIZE,0);
    
    gameTime.setFont(font);
    gameTime.setCharacterSize(20);
    gameTime.setPosition(SNAKE_SIZE+150,0);
    
    pauseString.setFont(font);
    pauseString.setCharacterSize(30);
    pauseString.setFillColor(Color::Magenta);
    pauseString.setPosition(SNAKE_SIZE+5, SCREEN_HEIGHT/2);
    pauseString.setString("Game paused (press P to continue)");
    
    points = 0;
    
    ostringstream sstreamBuffer;
    
    Clock playClock;
    float elapsedPauseTime = 0;
    
    Clock gameClock;
    float elapsedGameTime = 0.0f;
    float timeStep;
    
    Clock pauseTime;
    
    if(!snakeFast)
        timeStep = 0.35f; //Lower update time means faster snake movement
    else
        timeStep = 0.15f;
    
    Event event;
    
    bool directionChanged = true;
    
    while(gameState == Game::STARTED)
    {
        while(renderWindow.pollEvent(event))
        {
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                gameState=MENU;
            
            if(event.type == Event::Closed)
                gameState=ENDED;
            
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::P)
            {
               if(!gamePaused)
               {
                   gamePaused = true;
                   pauseTime.restart();
               }
               else
               {
                   gamePaused = false;
                   elapsedGameTime -= pauseTime.getElapsedTime().asSeconds();
                   
                   elapsedPauseTime += pauseTime.getElapsedTime().asSeconds();
               }
            }
        }
        
        if(Keyboard::isKeyPressed(Keyboard::Left) && directionChanged && !gamePaused)
        {
            snake.setDirection(Snake::LEFT);
            directionChanged = false;
        }
        
        if(Keyboard::isKeyPressed(Keyboard::Right) && directionChanged && !gamePaused)
        {
            snake.setDirection(Snake::RIGHT);
            directionChanged = false;
        }
        
        if(Keyboard::isKeyPressed(Keyboard::Up) && directionChanged && !gamePaused)
        {
            snake.setDirection(Snake::UP);
            directionChanged = false;
        }
        
        if(Keyboard::isKeyPressed(Keyboard::Down) && directionChanged && !gamePaused)
        {
            snake.setDirection(Snake::DOWN);
            directionChanged = false;
        }
        
        elapsedGameTime += gameClock.restart().asSeconds();
        
        //Dont update game when it's paused
        while(elapsedGameTime > timeStep && !gamePaused)
        {
            //If snake movement fails over game
            if(!snake.moveSnake())
                gameState = OVER;
            
            directionChanged = true;
            
            elapsedGameTime -= timeStep;
        }
        
        if(snake.getX() == food.getFoodX() && snake.getY() == food.getFoodY())
        {
            points++;
            snake.addSegment(food.getFoodX(), food.getFoodY());
            
            food.generateNewFood();
            
            //If new food is generated on snake, make new
            while(snake.collideWithSnake(food.getFoodX(), food.getFoodY()))
            {
                food.generateNewFood();
            }
        }
        
        //Convert int to string by ostringstream, prepare text and set sf::Text
        pointsText = "Points: ";
        sstreamBuffer << points;
        pointsText += sstreamBuffer.str();
        snakePoints.setString(pointsText);
        
        
        //Clear buffer
        sstreamBuffer.str("");
        sstreamBuffer.clear();
        
        timeText = "Time: ";
        
        //Dont update time when game is paused
        if(!gamePaused)
            playTime = playClock.getElapsedTime().asSeconds() - elapsedPauseTime;
        
        sstreamBuffer << playTime;
        timeText += sstreamBuffer.str();
        gameTime.setString(timeText);
        
        sstreamBuffer.str("");
        sstreamBuffer.clear();
        
        renderWindow.clear();
        
        renderWindow.draw(gameBorder);
        renderWindow.draw(snakePoints);
        renderWindow.draw(gameTime);
        snake.drawSnake(renderWindow);
        food.drawFood(renderWindow);
        
        if(gamePaused)
            renderWindow.draw(pauseString);
        
        renderWindow.display();
    }
    
    updateGame();
}
