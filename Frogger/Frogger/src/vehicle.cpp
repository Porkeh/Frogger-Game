#include "vehicle.h"

//main constructor
Vehicle::Vehicle(sf::Texture& tex, int x, int y, sf::IntRect TextureRect, int direction, int speed)
{
	//set up sprite
	size = sf::Vector2f(TextureRect.width,TextureRect.height);
	sprite.setScale(1,1);
	sprite.setOrigin(size.x/2,size.y/2);
	sprite.setPosition(x,y);
	sprite.setTexture(tex);
	sprite.setTextureRect(TextureRect);
	//set direction and speed
	Vehicle::iDirection = direction;
	velocity = sf::Vector2f(1,0);
	Vehicle::iSpeed = speed;
	
}
//default constructor
Vehicle::Vehicle()
{
}
//method to move the vehicle
void Vehicle::move()
{
	//set newPos to an empty Vector
	sf::Vector2f newPos = sf::Vector2f();
	//find the direction the vehicle is travelling in 
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
		//nmultiply 1 by the speed of the vehicle to get velocity
		velocity.x = 1*iSpeed;
		velocity.y = 0;
		//add velocity onto the sprite position
		newPos = sprite.getPosition() + velocity;
		//set the new position
		sprite.setPosition(newPos);
		break;
	case(2) :
		//moves log left
		//multiply 1 by the speed of the vehicle to get velocity
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


//getters and setters
sf::FloatRect Vehicle::GetGlobalBounds()
{
	sf::FloatRect rect = sprite.getGlobalBounds();
	return rect;
}
//checks if vehicle has gone offscreen
bool Vehicle::CheckLife()
{
	if(sprite.getPosition().x > 550 || sprite.getPosition().x < -50)
	{
		return false;
	}

	
	
		return true;
	
}


