#include "Tile.h"

Tile::Tile()
{
	mainRect.setSize(sf::Vector2f(32, 32));
	mainRect.setPosition(0, 0);


	mainRect.setFillColor(sf::Color::Green);
}


void Tile::setMainRectPosition(int x, int y)
{
	mainRect.setPosition(x, y);
}
