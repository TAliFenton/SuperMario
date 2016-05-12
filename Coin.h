#ifndef COIN_H
#define COIN_H
#include <SFML/Graphics.hpp>

class Coin
{
private:
	sf::Clock clock;
	sf::Texture cTexture;
	sf::IntRect rectCoin;
	sf::Sprite cSprite;
	bool isVisible;
public:
	Coin();
	sf::IntRect getSpriteRect() { return rectCoin; }
	sf::FloatRect getSpriteBounds() { return cSprite.getGlobalBounds(); }
	bool getIsVisible() const { return isVisible; }
	void setIsVisible(bool vis);
	void setPosition(int x, int y);
	void draw(sf::RenderWindow &window);
};

#endif
