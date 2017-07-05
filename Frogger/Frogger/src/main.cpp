#include "main.h"

//main 
int main()
{
	//create objects 
	//window object
	sf::RenderWindow window(sf::VideoMode(500,600), "Frogger");
	sf::Vector2f windowSize(window.getSize().x,window.getSize().y);
	//clock object
	sf::Clock clock;
	float fCurrentTime = clock.getElapsedTime().asSeconds();
	window.setPosition(sf::Vector2i(500,100));
	if(!spriteSheet.loadFromFile(".\\assets\\sprite_sheet.png"))
	{
		return 0;
	}
	bGameOver = false;
	sf::Font font;
	if(!font.loadFromFile(".\\assets\\fonts\\FORCEDSQUARE.TTF")) 
	{
		return 0;
	}

	Text countDown(font,100, sf::String("3"),sf::Vector2f(windowSize.x/2,windowSize.y/2), true);
	Text gameOverText(font,100,sf::String("Game\nOver!"), sf::Vector2f(windowSize.x/2-100,windowSize.y/2-200), true);
	Text gameOver2(font,20,sf::String("Press Space to play again"), sf::Vector2f(windowSize.x/2-100,windowSize.y/2+200), true);
	Frog player(spriteSheet);
	Text lifeText(font, 20, sf::String("Lives: "+ to_string(player.GetLives())),sf::Vector2f(400,560), true);
	
	//create premade vehicle objects to be copied into the vector
	Vehicle v1(spriteSheet,500,487,sf::IntRect(80,264,24,26), 2, 4);
	Vehicle v2(spriteSheet,-50,442,sf::IntRect(46,265,24,24), 1, 4);
	Vehicle v3(spriteSheet, 500, 397,sf::IntRect(10,267,28,20), 2, 4);
	Vehicle v4(spriteSheet,-50,352,sf::IntRect(11,301,23,21), 1, 3);
	Vehicle v5(spriteSheet, -50, 532, sf::IntRect(11,301,23,21),1,3);
	//create premade log ojbects to be copied into the vector
	Log l1(spriteSheet, -50, 262, sf::IntRect(7,198,116,21), 1, 5);
	Log l2(spriteSheet, 550, 217, sf::IntRect(7,198,116,21), 2, 4);
	Log l3(spriteSheet, -50, 172, sf::IntRect(7,198,116,21), 1, 4);
	Log l4(spriteSheet, 550, 127, sf::IntRect(7,198,116,21), 2, 5);
	Log l5(spriteSheet, -100, 82, sf::IntRect(7,167,177,23), 1, 4);
	//create the bases and put them in the array
	bases[0] = Base(spriteSheet,sf::FloatRect(5, 15, 50, 45));
	bases[1] = Base(spriteSheet,sf::FloatRect(115, 15, 50, 45));
	bases[2] = Base(spriteSheet,sf::FloatRect(225, 15, 50, 45));
	bases[3] = Base(spriteSheet,sf::FloatRect(335, 15, 50, 45));
	bases[4] = Base(spriteSheet,sf::FloatRect(445, 15, 50, 45));

	window.setVerticalSyncEnabled(true);
	//stop keys being held down
	window.setKeyRepeatEnabled(false);
	
	//main game loop
	while (window.isOpen())
	{
		//object to hold the event
		sf::Event event;
		//see if there are any events
		while(window.pollEvent(event))
		{
			//close the window when it is closed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			//if there is a key event
			if (event.type == sf::Event::KeyPressed)
			{
				//record the key code
				sf::Keyboard::Key key = event.key.code;
				//if it is space and game over. reset the game
				if(key == sf::Keyboard::Space)
				{
					if(bGameOver)
					{
						//reset the variables
						ResetGame(player);
						countDown.SetText(sf::String("3"));
						countDown.SetVisible(true);
						fCurrentTime = 0;
						//restart the clock for a new game
						clock.restart();
					}
				}
				else
				{
					//send the key code to the player to move
					player.move(key);
				}

			}
		}
		//these four if statements create the countdown clock at the start of the game
		//this stops the player from moving whilst the lanes can create some traffic
		//if greater than 1 elapsed time 2 seconds remaining
		if(clock.getElapsedTime().asSeconds() >= 1.0f)
		{
			countDown.SetText(sf::String("2"));
			
		}
		//if greater than 2 elapsed time 1 second remaining
		if(clock.getElapsedTime().asSeconds() >= 2.0f)
		{
			countDown.SetText(sf::String("1"));
			
		}
		//if the elapsed time is between 3 and 3.5. The game starts and the player can move
		if(clock.getElapsedTime().asSeconds() >= 3.0f && clock.getElapsedTime().asSeconds() <= 3.5f)
		{
			player.SetCanMove(true);
			countDown.SetText(sf::String("Go!"));
			
		}
		//any time after this hide the text
		if(clock.getElapsedTime().asSeconds() >= 3.5f)
		{
			countDown.SetVisible(false);
		}
		//record the elapse time
		float elapsedTime = clock.getElapsedTime().asSeconds();
		
		//if a second or more has passed spawn a vehicle or lag in each lane
		if(elapsedTime - fCurrentTime >= 1.0f)
		{
			lanes[0].push_back(v1);
			lanes[1].push_back(v2);
			lanes[2].push_back(v3);
			lanes[3].push_back(v4);
			lanes[4].push_back(v5);
			logs[0].push_back(l1);
			logs[0].push_back(l2);
			logs[0].push_back(l3);
			logs[0].push_back(l4);
			logs[0].push_back(l5);
			//reset the current time
			fCurrentTime = elapsedTime;
			

		}
		
		
		//loop through the array of vectors that stores the vehicles and perform logic
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < lanes[i].size(); j++)
			{
				//move the vehicle
				lanes[i].at(j).move();
				//if the vehicle intersects with the player
				if(lanes[i].at(j).GetGlobalBounds().intersects(player.GetGlobalBounds()) && player.GetCanMove())
				{
					//kill player
					player.Kill();
				}

			}
			//loop backwards through the loop for deletion
			for (int j = lanes[i].size()-1; j >= 0; j--)
			{
				//if the vehicle is offscreen then remove it from the vector
				if(lanes[i].at(j).CheckLife() == false)
				{
					lanes[i].erase(lanes[i].begin()+j);
				}
			}
		}

		//loop through the array of vectors that stores the logs and perform logic
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < logs[i].size(); j++)
			{
				//move the logs
				logs[i].at(j).move();
				//if the logs intersect the player
				if(logs[i].at(j).GetGlobalBounds().intersects(player.GetGlobalBounds()))
				{
				
					//set that the player is on the log
					player.SetOnLog(true);
					//move the player on the log it's intersecting with
					player.LogMove(logs[i].at(j).GetSpeed(), logs[i].at(j).GetDirection());
				}

			}
			//loop backwards through the loop for deletion
			for (int j = logs[i].size()-1; j >= 0; j--)
			{
				//check if the log is offscreen then remove it from the vector
				if(logs[i].at(j).CheckLife() == false)
				{
					logs[i].erase(logs[i].begin()+j);
				}
			
			}
		}

		//loop through the array of bases
		for(int i = 0; i < 5; i++)
		{
			//if the player intersects with a base
			if(player.GetGlobalBounds().intersects(bases[i].GetBase()))
			{
				//execute the player method for hitting a base
				player.Base();
				//set the sprite on the base hit to visible
				bases[i].SetVisible(true);
	
			}
		}
	


		//call the players update function to update itself
		player.Update(windowSize, lifeText);

		//if the player has ran out of lives then set game over
		if(player.GetLives() == 0)
		{
			bGameOver = true;
		}
	
		//create an int to count the bases
		int iWin = 0;
		//loop through the array of bases
		for(int i = 0; i < 5; i++)
		{
			//check if the base is visible
			if(bases[i].GetVisible() == true)
			{
				//if so increment the win
				iWin++;
				//if all 5 bases are visible
				if(iWin == 5)
				{
					//game is over
					bGameOver = true;
				}
			}
		}
	
		//if it's not game over then draw the normal screen. Otherwise draw the game over screen
		if(!bGameOver)
		{
			Draw(window, player, countDown,lifeText);
		}
		else
		{
			DrawGameOver(window,gameOverText, gameOver2);
		}
		
		
	}
	//exit the program
	return 0;
	
}
//draw loop
void Draw(sf::RenderWindow& window, Frog& player, Text text, Text livesText)
{
	//clear the screen
	window.clear(sf::Color::Yellow);
	//draw the background
	window.draw(bGround);
	//loop through the trafic llanes and draw the vehicles
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < lanes[i].size(); j++)
		{
			window.draw(lanes[i].at(j));
		}
	}
	//loop through the log lanes and draw the vehicles
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < logs[i].size(); j++)
		{
			window.draw(logs[i].at(j));
		}
	}
	//draw the visisble bases
	for(int i = 0; i < 5; i++)
	{
		if(bases[i].GetVisible())
		{
			window.draw(bases[i]);
		}
	}
	//draw the player
	window.draw(player);
	//if the text is visble so that it can be drawn to the screen. 
	if(text.GetVisible())
	{
		window.draw(text.GetText());
	}
	if(livesText.GetVisible())
	{
		window.draw(livesText.GetText());
	}
	//endloop
	window.display();

}

//draw function for when the game is over
void DrawGameOver(sf::RenderWindow& window, Text text, Text text2)
{
	//clear the background
	window.clear(sf::Color::Yellow);
	//draw the background
	window.draw(bGround);
	//draw any bases that the player achieved
	for(int i = 0; i < 5; i++)
	{
		if(bases[i].GetVisible())
		{
			window.draw(bases[i]);
		}
	}
	//output the game over text
	if(text.GetVisible())
	{
		window.draw(text.GetText());
	}
	//ask to play again in this text
	if(text2.GetVisible())
	{
		window.draw(text2.GetText());
	}
	//close the draw loop;
	window.display();
}


//function to reset the game
void ResetGame(Frog& player)
{
	//calls kill to reset the frog
	player.Kill();
	//sets the lives back to 3
	player.SetLives(3);

	//clears any logs and vehicles out of their vectors
	for (int i = 0; i < 5; i++)
	{
		logs[i].clear();
		lanes[i].clear();
	}
	//loops through the bases and makes sure they're invisible
	for(int i = 0; i < 5; i++)
	{
		bases[i].SetVisible(false);
	}
	//set that the player can move
	player.SetCanMove(false);
	//set that the gameOver timer iss till up
	bGameOver = false;
}