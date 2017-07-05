
#include"Text.h"

//main constructor
Text::Text(sf::Font& font, int size, sf::String string, sf::Vector2f pos, bool visible)
{
	text.setFont(font);
	text.setCharacterSize(size);
	text.setString(string);
	text.setPosition(pos);
	bVisible = visible;
}

//getters and setters
void Text::SetText(sf::String string)
{
	text.setString(string);
}
sf::Text Text::GetText()
{
	return text;
}

void Text::SetVisible(bool b)
{

	bVisible = b;

}

bool Text::GetVisible()
{
	return bVisible;
}