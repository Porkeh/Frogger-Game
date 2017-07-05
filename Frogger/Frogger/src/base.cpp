
#include "base.h"
//main constructor
Base::Base(sf::Texture& spriteSheet, sf::FloatRect rect)
{
	//set up sprite
	sprite.setScale(1,1);
	sprite.setOrigin(23/2,17/2);
	sprite.setPosition(rect.left+rect.width/2,rect.top+rect.height/2);
	sprite.setTexture(spriteSheet);
	sprite.setTextureRect(sf::IntRect(12,368,23,17));
	//rectangle bounds of the base
	base = rect;
	//active but not visible
	bActive = true;
	bVisible = false;
}
//default constructor
Base::Base()
{
}
//getters and setters
sf::FloatRect Base::GetBase()
{
	return base;
}

bool Base::GetVisible()
{
	return bVisible;
}

void Base::SetVisible(bool b)
{
	bVisible = b;
}