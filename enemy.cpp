#include "enemy.h"
//#include "ResourcePath.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace std;

Enemy::Enemy(){
	if (!pTexture.loadFromFile("images/enemy.png"))
		cout << "Could not load image from file" << endl;
	rectEnemy.left = 0;
	rectEnemy.top = 0;
	isVisible = true;
	move.left = 0;
	move.top = 0;
	move.width = 250;
	move.height = 248;
	rectEnemy.width = 250;
	rectEnemy.height = 248;
	pSprite.setTexture(pTexture);
	pSprite.setTextureRect(rectEnemy);
	counter = 0;

	rect.setSize(sf::Vector2f(250 * .1, 248 * .1));
	TopRect.setSize(sf::Vector2f(3 * 2, 6 * 2));
	LeftRect.setSize(sf::Vector2f(6 * 2, 3 * 2));
	RightRect.setSize(sf::Vector2f(6 * 2, 3 * 2));
	BottomRect.setSize(sf::Vector2f(3 * 2, 6 * 2));

	pSprite.setScale(.1, .1);

	//pSprite.move(30,375);
	direction = left;
	isDead = false;

	TopRect.setPosition(rect.getPosition().x + rect.getSize().x / 2, rect.getPosition().y);
	LeftRect.setPosition(rect.getPosition().x, rect.getPosition().y + rect.getSize().y / 2);
	RightRect.setPosition(rect.getPosition().x + rect.getSize().x, rect.getPosition().y + rect.getSize().y / 2);
	BottomRect.setPosition(rect.getPosition().x + rect.getSize().x / 2, rect.getPosition().y + rect.getSize().y);

	LeftRect.setFillColor(sf::Color::Red);
	RightRect.setFillColor(sf::Color::Blue);
	BottomRect.setFillColor(sf::Color::Black);
	TopRect.setFillColor(sf::Color::Yellow);

	gravityAcceleration = 15;// the acceleration to gravity which brings the player back down
	speedValue = 20; //this is the rate at which we are bringing loompas back down to the ground

}


void Enemy::update()//update the position of the rectangles
{
	TopRect.setPosition(rect.getPosition().x + rect.getSize().x / 2 - 3, rect.getPosition().y - TopRect.getSize().y);
	LeftRect.setPosition(rect.getPosition().x - LeftRect.getSize().x, rect.getPosition().y + rect.getSize().y / 2);
	RightRect.setPosition(rect.getPosition().x + rect.getSize().x, rect.getPosition().y + rect.getSize().y / 2);
	BottomRect.setPosition(rect.getPosition().x + rect.getSize().x / 2 - 3, rect.getPosition().y + rect.getSize().y);
}

void Enemy::moveLeft() {
	if (isDead == false) {
		if (direction == right)
			move.left = 0;
		if (direction == right || rectEnemy.left == 250)
			rectEnemy.left = 250 * 2;
		if (clock.getElapsedTime().asSeconds() > 0.10f) {
			if (rectEnemy.left == 250 * 2) {
				rectEnemy.left = 0;
				pSprite.move(-15, 0);
				rect.move(-15, 0);
				move.left -= 10;
			}
			else {
				rectEnemy.left += 250;
				pSprite.move(-12, 0);
				rect.move(-12, 0);
				move.left -= 10;
			}
			pSprite.setTextureRect(rectEnemy);
			clock.restart();
			direction = left;
		}
	}
	else
	{
		pSprite.move(-300, 400);
		rect.move(-300, 400);
	}
}


void Enemy::moveRight() {
	if (isDead == false) {
		if (direction == left)
			move.left = 0;
		if (direction == left || rectEnemy.left == 250 * 2)
			rectEnemy.left = 0;
		if (clock.getElapsedTime().asSeconds() > 0.10f) {
			if (rectEnemy.left == 250) {
				rectEnemy.left = 0;
				pSprite.move(10, 0);
				rect.move(10, 0);
				move.left += 10;
			}
			else {
				rectEnemy.left += 250;
				pSprite.move(10, 0);
				rect.move(10, 0);
				move.left += 10;//not sure exactly where left starts but wokr if done like this
			}
			pSprite.setTextureRect(rectEnemy);
			clock.restart();
			direction = right;
		}
	}
	else {
		pSprite.move(-300, 400);
		rect.move(-300, 400);
	}
}

void Enemy::setPosition(int x, int y)
{
	//pSprite.move(0, 0);
	pSprite.setPosition(x, y);
	rect.setPosition(x, y);

}


//****************************** Player Intersecting with Goomba **************************

void Enemy::setDead(sf::RenderWindow& Window) {
	rectEnemy.left = 255 * 2;
	pSprite.setTextureRect(rectEnemy); //set texture to die
	
}

//If the enemy is still visible
void Enemy::setIsVisible(bool vis) {
	isVisible = vis;
}

//Making sure that the intersection when it is intersected with the X axis it enemy does not die
bool Enemy::isIntersectingX(const float ob1) {
	if (abs(pSprite.getPosition().x - ob1) <= 25) //sets the range for x
		return true;
	else
		return false;
}

//The Intersection with the Y is greater than enemy hieght and if so the goomba will die
bool Enemy::isIntersectingY(const float ob1Y) {
	//cout << "******************" << endl;
	//cout << "This is y: " << pSprite.getPosition().y << " " << "This is x: " << ob1Y << endl;
	//cout << "******************" << endl;
	if ((pSprite.getPosition().y - ob1Y) > 23.5 && (pSprite.getPosition().y - ob1Y) < 30.5) //sets the width
		return true;
	else
		return false;
}
//*************************************************************************************

void Enemy::draw(sf::RenderWindow &window) {
	window.draw(pSprite);
}


void Enemy::gravity(float deltaTime)
{
	if (speedValue > 0)
		speedValue = 0;

	//cout << "Inside Gooompa set gravity function\n";
	speedValue -= gravityAcceleration * deltaTime;// by this is what makes mario go up in air
	pSprite.move(0, -speedValue);// setting up the sprite value to move accordingly
	rect.move(0, -speedValue);
}

bool Enemy::checkCollisionTile(Tile p, int position)// check collision with a tile
{

	//cout << "Counter = " << counter << endl;

	if (rect.getPosition().x <= position)
	{

		if (counter == 0)
		{
			counter = 3;

		}

		if (LeftRect.getGlobalBounds().intersects(p.mainRect.getGlobalBounds()) && rect.getGlobalBounds().intersects(p.mainRect.getGlobalBounds()))
		{
			counter = 2;
		}

		if (RightRect.getGlobalBounds().intersects(p.mainRect.getGlobalBounds()) && rect.getGlobalBounds().intersects(p.mainRect.getGlobalBounds()))
		{
			counter = 3;
		}

		switch (counter)
		{
			case 2:
			{
			//	cout << "Inside switch case 2\n";
				moveRight();
				break;
			}

			case 3:
			{
				// << "Inside switch case 3\n";
				moveLeft();
				break;

			}

		}

	//	cout << "Counter: " << counter << endl;

	}
	if (BottomRect.getGlobalBounds().intersects(p.mainRect.getGlobalBounds()) && rect.getGlobalBounds().intersects(p.mainRect.getGlobalBounds()))
	{
		rect.setPosition(rect.getPosition().x, p.mainRect.getPosition().y - 25);
		pSprite.setPosition(rect.getPosition().x, p.mainRect.getPosition().y - 25);
		return true;
	}

	//cout << "Before Top check if statement\n";
	if (TopRect.getGlobalBounds().intersects(p.mainRect.getGlobalBounds()) && rect.getGlobalBounds().intersects(p.mainRect.getGlobalBounds()))
	{
		rect.setPosition(rect.getPosition().x, p.mainRect.getPosition().y + p.mainRect.getSize().y + 70);
		pSprite.setPosition(rect.getPosition().x, p.mainRect.getPosition().y + p.mainRect.getSize().y + 70);
		return true;
	}
	//cout << "Before Left check if statement\n";
	if (LeftRect.getGlobalBounds().intersects(p.mainRect.getGlobalBounds()) && rect.getGlobalBounds().intersects(p.mainRect.getGlobalBounds()))
	{
		//cout << "Mario collides with left block\n";
		rect.setPosition(p.mainRect.getPosition().x + p.mainRect.getSize().x + 5, rect.getPosition().y);
		pSprite.setPosition(p.mainRect.getPosition().x + p.mainRect.getSize().x + 5, rect.getPosition().y);
	//	moveRight();
		return true;
	}
	//cout << "Before Right check if statement\n";
	if (RightRect.getGlobalBounds().intersects(p.mainRect.getGlobalBounds()) && rect.getGlobalBounds().intersects(p.mainRect.getGlobalBounds()))
	{
		rect.setPosition(p.mainRect.getPosition().x - 50, rect.getPosition().y);
		pSprite.setPosition(p.mainRect.getPosition().x - 50, rect.getPosition().y);
	//	moveLeft();
		return true;
	}

	//cout<<"No collision in check collision tile\n";
	return false;



}

