#ifndef COIN_H
#define COIN_H
#include "Player.h"
class Coin
{
	private:
		sf::Clock clock;
		sf::Texture cTexture;
		sf::IntRect rectCoin;
		sf::Sprite cSprite;
	public:
		Coin();
		~Coin();
		void setPosition(int x, int y);
		void draw(sf::RenderWindow &window);
};

#endif
