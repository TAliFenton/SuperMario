#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "Coin.h"
#include"Tile.h"
#include"enemy.h"

class Player {
private:
	sf::Clock clock;
	//Texture class holds image data. Its purpose is to load in an image.
	//we make a pointer to the sprite's data so that we could display it to the screen
	sf::Texture pTexture;
	sf::IntRect rectPlayer;
	sf::RectangleShape rect;
	double Bottom, Left, Right, Top;
	sf::Sprite pSprite;
	enum lastDirectionFacing { up, down, left, right };
	int direction;
	bool isAlive;
	unsigned int playerLives;
	unsigned int coinCount;
	//Dario Stuff:
	float jumpValue;// how many pixels go up
	float gravityAcceleration;// the acceleration to gravity which brings the player back down
	float marioMass;// the weight of mario
public:
	//overloaded constructor:
	Player();
	void moveLeft();
	void moveRight();
	void dead();
	void flag();
	void addCoinCount();
	void changeJump();
	bool getIsAlive() const { return isAlive; }
	void reset();
	bool decreasePlayerLives();
	int getPlayerLives() const { return playerLives; }
	void setIsAlive(bool isAlive) { this->isAlive = isAlive; }
	int getCoinCount() const { return coinCount; }
	bool checkIfCoinIsTouched(Coin c);
	void draw(sf::RenderWindow &window);
	void idle();

	//Dario Stuff:
	double speedValue; //how fast he jumps and ocmes back down to the ground
	void setPosition(int x, int y);
	void rectSetPosition(int x, int y);
	int getRectPositionX() { return rect.getPosition().x; }
	int getRectPositionY() { return rect.getPosition().y; }
	void moveDown();
	int getPositionX();
	int getPositionY();
	void gravity(float deltaTime);
	int getTop() { return Top; }
	int getBottom() { return Bottom; }
	int getRight() { return Right; }
	int getLeft() { return Left; }
	bool checkCollisionTile(Tile& p);
	void checkCollisionEnemy(Enemy& p, int& score);
	void update();

	sf::RectangleShape TopRect;
	sf::RectangleShape BottomRect;
	sf::RectangleShape RightRect;
	sf::RectangleShape LeftRect;

	sf::RectangleShape getMarioRect() { return rect; }

	//accesors
	sf::Sprite getPlayerSprite() { return pSprite; }
	float getJumpValue() const { return jumpValue; }
	float getMarioMass() const { return marioMass; }
	~Player();
};

#endif
