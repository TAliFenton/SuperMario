#include "Coin.h"
#include <iostream>
using namespace std;

Coin::Coin()
{
	if (!cTexture.loadFromFile("images/coin.png"))
		cout << "The coin sprite cannot be loaded.\n";
	rectCoin.left = 0;
	rectCoin.top = 0;
	rectCoin.width = 56;
	rectCoin.height = 56;
	cSprite.setTexture(cTexture);
	cSprite.setTextureRect(rectCoin);
	cSprite.move(350, 350);
	cSprite.setScale(.4, .4);
}

void Coin::setPosition(int x, int y) 
{
	cSprite.move(0, 0);
	cSprite.setPosition(x, y);
}


Coin::~Coin()
{
}

void Coin::draw(sf::RenderWindow &window)
{
	window.draw(cSprite);
}
