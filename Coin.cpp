#include "Coin.h"
#include <iostream>
using namespace std;

Coin::Coin()
{
	if (!cTexture.loadFromFile("images/coin.png"))
		cout << "The coin sprite cannot be loaded.\n";
	rectCoin.left = 0;
	rectCoin.top = 0;
	rectCoin.width = 55;
	rectCoin.height = 55;
	cSprite.setTexture(cTexture);
	cSprite.setTextureRect(rectCoin);
	cSprite.setPosition(350, 350);
	cSprite.setScale(.4, .4);
	isVisible = true;
}

void Coin::setPosition(int x, int y) {
	cSprite.setPosition(x, y);
}

void Coin::setIsVisible(bool vis) {
	isVisible = vis;
	rectCoin.width = 0;
	rectCoin.height = 0;
	cSprite.setTextureRect(rectCoin);
}


void Coin::draw(sf::RenderWindow &window)
{
	window.draw(cSprite);
}
