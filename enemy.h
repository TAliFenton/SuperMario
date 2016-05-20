#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include"Tile.h"
class Enemy {
private:
	sf::Clock clock;
	sf::Texture pTexture;
	sf::IntRect rectEnemy;
	sf::IntRect move;//This rectangle will stay behind the sprite creating a new rectangle

	sf::RectangleShape rect;

	sf::Sprite pSprite;
	bool isVisible;
	enum lastDirectionFacing { left, right };
	int direction;
	bool isDead;
	int counter;
public:
	//***********************************************************


	sf::RectangleShape TopRect;
	sf::RectangleShape BottomRect;
	sf::RectangleShape RightRect;
	sf::RectangleShape LeftRect;

	sf::RectangleShape getMainRect() const { return rect; }


	float gravityAcceleration;// the acceleration to gravity which brings the player back down
	double speedValue; //this is the rate at which we are bringing loompas back down to the ground
	bool checkCollisionTile(Tile p, int position);
	void update();

	Enemy();
	//Precondition: Has to be set with defualt numbers or statements
	//Postcondition: Should run the default values given when runs
	//***********************************************************
	void setIsDead(bool dead) { isDead = dead; }
	int getDirection()const { return direction; }
	bool getIsDead() const { return isDead; }
	void setDead(sf::RenderWindow& Window);
	//Precondition:
	//Postcondition:
	//***********************************************************
	void moveRight();
	//Precondition: Get the image for right to move right
	//Postcondition: successfully move the sprite right
	//***********************************************************
	void moveLeft();
	//Precondition: Get the image for the left to move left
	//Postcondition: successfully move the sprite
	//***********************************************************
	void draw(sf::RenderWindow &window);
	//Precondition: will draw the image
	//Postcondition: successfully displays the image
	//***********************************************************
	sf::Sprite getSprite()const { return pSprite; }
	//Precondition:
	//Postcondition:
	//***********************************************************
	sf::IntRect getRect()const { return rectEnemy; }
	//Precondition:
	//Postcondition:
	//***********************************************************
	bool isIntersectingX(const float ob1);
	//Precondition:
	//Postcondition:
	//***********************************************************
	bool isIntersectingY(const float ob1);
	//Precondition:
	//Postcondition:
	//***********************************************************
	bool getIsVisible()const { return isVisible; }
	//Precondition:
	//Postcondition:
	//***********************************************************
	void setIsVisible(bool vis);
	//Precondition:
	//Postcondition:
	int getPositionX()const { return pSprite.getPosition().x; }
	//Precondition:
	//Postcondition:
	//***********************************************************
	int getPositionY()const { return pSprite.getPosition().y; }
	//Precondition:
	//Postcondition:
	//***********************************************************
	void setPosition(int x, int y);

	void gravity(float deltaTime);
};

#endif /* enemy_hpp */
