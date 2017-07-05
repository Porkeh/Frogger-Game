#include "bGround.h"

BGround::BGround()
{
	//load background
	skin.loadFromFile(".\\assets\\froggerbg.png");
	//setup sprite
	sprite.setTexture(skin);
	sprite.setScale(1,1);
	sprite.setOrigin(0,0);
	sprite.setPosition(0,0);
}

