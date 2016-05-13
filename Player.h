#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "Coin.h"

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
		//Dario Stuff:
		float jumpValue;// how many pixels go up
		float gravityAcceleration;// the acceleration to gravity which brings the player back down
		float marioMass;// the weight of mario
	public:
		//overloaded constructor:
		Player();
		void moveLeft();
		void moveRight();
		void moveDown();
		void addCoinCount();
		int getCoinCount() const { return coinCount; }
		bool checkIfCoinIsTouched(Coin c);
		void draw(sf::RenderWindow &window);
		void checkIsAlive(bool isAlive);
		void idle();

		//Dario Stuff:
		float speedValue; //how fast he jumps and ocmes back down to the ground
		void setPosition(int x, int y);
		int getPositionX();
		int getPositionY();
		void jump(float deltaTime);

		//accesors
		sf::Sprite getPlayerSprite() const { return pSprite; }
		float getJumpValue() const { return jumpValue; }
		float getMarioMass() const { return marioMass; }
		~Player();
};

#endif
