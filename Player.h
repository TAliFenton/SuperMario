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
	sf::RectangleShape TopRect;
	sf::RectangleShape BottomRect;
	sf::RectangleShape RightRect;
	sf::RectangleShape LeftRect;


	Player();// Constructor for the Player class. Sets the default values.
	//***********************************************************************
	void moveLeft();
	//Precondition: the sprite image for left will move left
	//Postcondition: Sprite will successfully move left
	//Summary: The Sprite image will show up on the screen and be able to move left
	//*********************************************************************
	void moveRight();
	//Precondition: the sprite image for right will move right
	//Postcondition: Sprite will successfully move right
	//Summary: The Sprite image will show up on the screen and be able to move right
	//*********************************************************************
	void dead();
	//Precondition: the image for dead will show
	//Postcondition: Successfully show right
	//Summary: The dead image will show up on the screen
	//*********************************************************************
	void addCoinCount();
	//Precondition: add the coins up
	//Postcondition: successfully adds all the coins
	//Summary: Adds all the coins together
	//*********************************************************************
	void changeJump();
	//Precondition: checks wether the users direction is right.
	//Postcondition: If the users direction is right then it executes towards
	//the right else it executes towards the left.
	//Summary: Decides the outcome of the jump.
	//*********************************************************************
	void reset();
	//Precondition: marios lives have decreased and he has to be reset.
	//Postcondition: Mario gets reset at a specific (x,y) coordinate.
	//his lives also get reset.
	//Summary: Mario gets positioned at a default position.
	//*********************************************************************
	bool decreasePlayerLives();
	//Precondition: takes away life when mario dies
	//Postcondition: successfully takes away a life
	//Summary: Takes away a life when the player dies
	//*********************************************************************
	bool checkIfCoinIsTouched(Coin c);
	//Precondition: checks if the coin and player touched
	//Postcondition: Successfully checks if they touched
	//Summary: Sees if the coin and the player have touched so the coin will not be there
	//*********************************************************************
	void draw(sf::RenderWindow &window);
	//Precondition: Draw the all the images for mario
	//Postcondition: Successfully draws the image
	//Summary: Draws the image onto the screen when it is called
	//*********************************************************************
	void idle();
	//Precondition: A sprite gets set accordingly to the direction that
	//Mario is facing.
	//Postcondition: A sprite gets set according to the left and right directions.
	//Summary: Gets the appropriate sprite within the sprite sheet.
	//*********************************************************************
	double speedValue;
	//Precondition: Detects the speed at which mario jumps
	//Postcondition: Mario gets brought down with a gravity algorithm.
	//Summary: Detects how fast mario jumps and how fast he comes back down to
	//the ground.
	//*********************************************************************
	void rectSetPosition(int x, int y);
	//Precondition: A rectangle gets set in contrast to the positioning of the player.
	//Postcondition: After detecting the point location of mario a rectangle gets set.
	//Summary: A rectangle gets loaded according to the rectangle position.
	//*********************************************************************
	void moveDown();
	//Precondition: Sprite has been assigned to appropriate image
	//Postcondition:Once Mario reaches the flag pole, this function will be called and Mario will move down the pole bringing the flag down.
	//Summary: This function is neccesary for when Mario reaches the flag pole, it can bring it down and simulate Mario coming down the flag pole.
	//*********************************************************************
	void gravity(float deltaTime);
	//Precondition:A variable that acts as a counter increasing every second is passed into the function
	//Postcondition: As a result, this function is not going to return anything, it increases acceleration to bring Mario back to ground.
	//Summary: This function is called to bring Mario back down to ground, for if he jumps, he will come down simulating gravity.
	//*********************************************************************
	bool checkCollisionTile(Tile p);
	//Precondition: The tiles need to be assigned thorough out our map
	//Postcondition: This will return true if Mario is touching one of our blocks
	//Summary: This function will be called in our main driver and check to see if Mario is touching the tubes, blocks, or the floor.
	//*********************************************************************
	void checkCollisionEnemy(Enemy& p);
	//Precondition: checks if player collide with enemy
	//Postcondition: Successfully checks if player collides with enemy
	//Summary: The player hits the enemy the player will dead
	//*********************************************************************
	void update();
	//Precondition:The rectangle around Mario have created and initialized
	//Postcondition: It is called in our Main driver for we need to update the position of the rectangles around Mario
	//Summary: This function is necessary to update the rectangles around Mario so we can detect collection around our Map
	//*********************************************************************


// Getters and setters.
	void setIsAlive(bool isAlive) { this->isAlive = isAlive; }
	void setPosition(int x, int y);

	sf::RectangleShape getMarioRect() { return rect; }
	sf::Sprite getPlayerSprite() { return pSprite; }
	float getJumpValue() const { return jumpValue; }
	float getMarioMass() const { return marioMass; }
	int getCoinCount() const { return coinCount; }
	int getPlayerLives() const { return playerLives; }
	bool getIsAlive() const { return isAlive; }
	int getRectPositionX() { return rect.getPosition().x; }
	int getRectPositionY() { return rect.getPosition().y; }
	int getPositionX();
	int getPositionY();
	int getTop() { return Top; }
	int getBottom() { return Bottom; }
	int getRight() { return Right; }
	int getLeft() { return Left; }
	~Player();


};

#endif
