#include "frog.h"

//main constructor for the frog
Frog::Frog(sf::Texture& spriteSheet)
{
	//set up sprite
	size = sf::Vector2f(23,17);
	skin = spriteSheet;
	
	sprite.setScale(1,1);
	sprite.setOrigin(23/2,17/2);
	sprite.setPosition(250,600-(46/2));
	sprite.setTexture(skin);
	sprite.setTextureRect(sf::IntRect(12,368,23,17));
	//set lives to 3
	iLives = 3;
	//set booleans to false
	bCanMove = false;
	bOnLog = false;
	//set animation properties to false
	bIsAnim = false;
	iFrameCount = 0;
	int iRotation = 0;
	int iDistanceX = 0;
	int iDistanceY = 0;
	
	
}


//the update function which is called everytime the main updates
void Frog::Update(sf::Vector2f windowSize, Text& text)
{
	
	//call the next animation frame. this also moves the player
	Animate();
	//update the life count text
	text.SetText(sf::String("Lives: " + std::to_string(iLives)));
	//check if the player is in water but not on a log and an animation isnt playing
	if(sprite.getPosition().y < 300 && bOnLog == false)
	{
		if(!bIsAnim)
		{
			//kill the frog 
			Kill();
		}
	}
	//checks if the player has gone off screen or about to
	//kills the player if offscreen
	if(sprite.getPosition().y-size.y/2 < 0)
		{
			
			Kill();
		}
	if(sprite.getPosition().x-size.x/2 < 0 && !bIsAnim)
		{
			
			Kill();
		}
	if(sprite.getPosition().y+size.y/2 > windowSize.y)
		{
			
			Kill();
		}
	if(sprite.getPosition().x+size.x/2 > windowSize.x && !bIsAnim)
		{
			Kill();
			
		}
	//assume a frog is not on a log
	bOnLog = false;
	
}

//this method moves the frog if its on a log
//it takes the log speed and direction that the frog is intersecting
void Frog::LogMove(int iSpeed, int direction)
{
	if ( direction == 1)
	{
		//move the player by the speed of the log
		sprite.setPosition(sprite.getPosition().x + iSpeed,sprite.getPosition().y );
	}

	if (direction == 2)
	{
		//move the player by the speed of the log
		sprite.setPosition(sprite.getPosition().x - iSpeed, sprite.getPosition().y );
	}
}

//the method to move the player. takes keyboard input and decides what to do 

void Frog::move(sf::Keyboard::Key key)
{
	//checks if the frog can move
	if(bCanMove)
	{
		//if moving up
		if(key == sf::Keyboard::W || key == sf::Keyboard::Up)
		{
			//stop the current animation playing
			StopAnimation();
			//set up the parameters for the up animation
			iRotation = 0;
			iDistanceX = 0;
			iDistanceY = -5;
			iFinalFrame = 8;
			//enable animation
			bIsAnim = true;
	
		
		
		}
		//if moving left
		if(key == sf::Keyboard::A || key == sf::Keyboard::Left)
		{
			//stop the current animation playing
			StopAnimation();
			//set up the parameters for the left animation
			iRotation = 270;
			iDistanceX = -5;
			iDistanceY = 0;
			iFinalFrame = 10;
			//enable animation
			bIsAnim = true;
		
		
		}
		//if moving down
		if(key == sf::Keyboard::S || key == sf::Keyboard::Down)
		{
			//stop the current animation playing
			StopAnimation();
			//set up the parameters for the down animation
			iRotation = 180;
			iDistanceX = 0;
			iDistanceY = 5;
			iFinalFrame = 8;
			//enable animation
			bIsAnim = true;
	
		
		}
		// if moving right
		if(key == sf::Keyboard::D || key == sf::Keyboard::Right)
		{
			//stop the current animation playing
			StopAnimation();
			//set up the parameters for right animation
			iRotation = 90;
			iDistanceX = 5;
			iDistanceY = 0;
			iFinalFrame = 10;
			//enable animation
			bIsAnim = true;
		
		}
	
	}
	
}

//method to stop the current animation playing
 void Frog::StopAnimation()
 {
	 //resets all animation parameters to default to stop animation
	 iRotation = 0;
	 iDistanceX = 0;
	 iDistanceY = 0;
	 iFinalFrame = 0;
	 bIsAnim = false;
	 iFrameCount = 0;
	 bCanMove = true;
 }

 //method to animate and move the sprite
void Frog::Animate()
{
	//if animation is playing
	if(bIsAnim)
	{
		//move the sprite
		sprite.move(iDistanceX,iDistanceY);
		//make sure playing can't move
		if(iFrameCount ==1)
		{
		bCanMove = false;
		}
		
		
		//change the texture rectangle for animation
		if(iFrameCount == 2)
		{
			sprite.setTextureRect(sf::IntRect(46,367,22,25));
			sprite.setRotation(iRotation);

		}
		//allow the player to move before the animation ends. This will allow for a smoother feel. 
		if(iFrameCount ==6)
		{
			bCanMove = true;
		}
		//if the animation has ended, stop it and set the texture back to default
		if(iFrameCount >= iFinalFrame)
		{
			sprite.setTextureRect(sf::IntRect(12,368,23,17));
			bIsAnim = false;
			bCanMove = true;
			iFrameCount = 0;
		
			
		}

		//increment the frame count
		iFrameCount++;
	}

	

}


//method to kill the frog
void Frog::Kill()
{
	//set the position back to the start
	sprite.setPosition(250,600-(46/2));
	//take off a life
	iLives--;
	//disable any current booleans
	bOnLog = false;
	bIsAnim = false;
	//allow the player to move
	bCanMove = true;
}


//method for when the player enters a base
//same logic as Kill but without subtracting a life
void Frog::Base()
{
	sprite.setPosition(250,600-(46/2));
	bIsAnim = false;
	bCanMove = true;
}

//getters and setters
int Frog::GetLives()
{
	return iLives;
}

void Frog::SetCanMove(bool b)
{
	bCanMove = b;
}

void Frog::SetLives(int i)
{
	iLives = i;
}

bool Frog::GetCanMove()
{
	return bCanMove;
}
void Frog::SetOnLog(bool b)
{
	bOnLog = b;
}
sf::FloatRect Frog::GetGlobalBounds()
{
	sf::FloatRect rect = sprite.getGlobalBounds();
	return rect;
}