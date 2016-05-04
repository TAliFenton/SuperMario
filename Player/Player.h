#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

class Player {
private:
	sf::Clock clock;
	//Texture class holds image data. Its purpose is to load in an image.
	//we make a pointer to the sprite's data so that we could display it to the screen
	sf::Texture pTexture;
	sf::IntRect rectPlayer;
	sf::Sprite pSprite;
	enum lastDirectionFacing { up, down, left, right };
	int direction;
	bool isAlive;
	unsigned int playerLives;
	unsigned int coinCount;
public:
	//overloaded constructor:
	Player();
	void moveLeft();
	void moveRight();
	//void update(float dt);
	void draw(sf::RenderWindow &window);
	void checkIsAlive(bool isAlive);
	void idle();
	~Player();
};

#endif

