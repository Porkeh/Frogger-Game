#include "log.h"

//main constructor
Log::Log(sf::Texture& tex, int x, int y, sf::IntRect TextureRect, int direction, int speed)
{
	//set up sprite
	size = sf::Vector2f(TextureRect.width,TextureRect.height);
	sprite.setScale(1,1);
	sprite.setOrigin(size.x/2,size.y/2);
	sprite.setPosition(x,y);
	sprite.setTexture(tex);
	sprite.setTextureRect(TextureRect);
	//set direction and speed
	Log::iDirection = direction;
	velocity = sf::Vector2f(1,0);
	Log::iSpeed = speed;
}

//method to move the log
void Log::move()
{
	//set newPos to an empty Vector
	sf::Vector2f newPos = sf::Vector2f();
	//find the direction the log is travelling in
	switch(iDirection)
	{
	case(0) :
		//moves up. never called
		velocity.x = 0;
		velocity.y = -1*iSpeed;
		newPos = sprite.getPosition() + velocity;
		break;
	case(1) : 
		//moves log right
		//multiply 1 by the speed of the log to get velocity
		velocity.x = 1*iSpeed;
		velocity.y = 0;
		//add velocity onto the sprite position
		newPos = sprite.getPosition() + velocity;
		//set the new position
		sprite.setPosition(newPos);
		break;
	case(2) :
		//moves log left
		//multiply 1 by the speed of the log to get velocity
		velocity.x = -1*iSpeed;
		velocity.y = 0;
		//add velocity onto the sprite position
		newPos = sprite.getPosition() + velocity;
		//set the new position
		sprite.setPosition(newPos);
		break;
	case(3) :
		//moves down. never called
		velocity.x = 0;
		velocity.y = 1*iSpeed;
		newPos = sprite.getPosition() + velocity;
		sprite.setPosition(newPos);
		break;
	}
}
//checks if the log is still on screen. 
bool Log::CheckLife()
{
	if(sprite.getPosition().x > 700 || sprite.getPosition().x < -200)
	{
		return false;
	}


	return true;
}
//getters and setters
sf::FloatRect Log::GetGlobalBounds()
{
	sf::FloatRect rect = sprite.getGlobalBounds();
	return rect;
}

int Log::GetSpeed()
{
	return iSpeed;
}

int Log::GetDirection()
{
	return iDirection;
}