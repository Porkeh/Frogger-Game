
#include "DrawableSprite.h"
//default constructor
DrawableSprite::DrawableSprite()
{

	
	
}
//draw function for children to call to draw themselves
void DrawableSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

