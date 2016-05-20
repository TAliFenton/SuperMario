#include "Player.h"
#include <iostream>
#include<cmath>
using namespace std;

Player::Player()
{
	if (!pTexture.loadFromFile("images/MarioNew.png"))
		cout << "The player sprite cannot be loaded.\n";
	//IntRect objects hold 4 parameters: (Left/x-coordinate, Top/y-coordinate, Width, Height)
	rectPlayer.left = 0;
	rectPlayer.top = 0;
	rectPlayer.width = 93;
	rectPlayer.height = 140;
	pSprite.setTexture(pTexture);
	pSprite.setTextureRect(rectPlayer);
	//I added "playerImage.move(0, 350);" because I want to have Mario start at those specific coordinates [0, 350] instead of having it at the default which is (0, 0) [the upper left corner of the window]
	rect.setPosition(5, 345);
	pSprite.setPosition(rect.getPosition().x, rect.getPosition().y + 10 );
	//rect.setSize(sf::Vector2f(95,142 / 2));
	pSprite.setScale(.4, .4);
	direction = right;
	isAlive = true;
	playerLives = 3;
	coinCount = 0;

	//Dario Stuff:
	jumpValue = 500;
	gravityAcceleration = 8;
	marioMass = 35;
	speedValue = 0;

	rect.setSize(sf::Vector2f(95 * .4, 142 * .4));
	rect.setFillColor(sf::Color::Blue);

	TopRect.setSize(sf::Vector2f(3 * 2, 12 * 2));
	LeftRect.setSize(sf::Vector2f(15 * 2, 3 * 2));
	RightRect.setSize(sf::Vector2f(15 * 2, 3 * 2));
	BottomRect.setSize(sf::Vector2f(3 * 2, 12 * 2));

	TopRect.setPosition(rect.getPosition().x + rect.getSize().x / 2, rect.getPosition().y);
	LeftRect.setPosition(rect.getPosition().x, rect.getPosition().y + rect.getSize().y / 2);
	RightRect.setPosition(rect.getPosition().x + rect.getSize().x, rect.getPosition().y + rect.getSize().y / 2);
	BottomRect.setPosition(rect.getPosition().x + rect.getSize().x / 2, rect.getPosition().y + rect.getSize().y);

	LeftRect.setFillColor(sf::Color::Red);
	RightRect.setFillColor(sf::Color::Blue);
	BottomRect.setFillColor(sf::Color::Black);
	TopRect.setFillColor(sf::Color::Yellow);

}

Player::~Player()
{

}
void Player::rectSetPosition(int x, int y)
{
	rect.setPosition(x, y);

}

void Player::update()//update the position of the rectangles
{
	TopRect.setPosition(rect.getPosition().x + rect.getSize().x / 2 - 3, rect.getPosition().y - TopRect.getSize().y);
	LeftRect.setPosition(rect.getPosition().x - LeftRect.getSize().x, rect.getPosition().y + rect.getSize().y / 2);
	RightRect.setPosition(rect.getPosition().x + rect.getSize().x, rect.getPosition().y + rect.getSize().y / 2);
	BottomRect.setPosition(rect.getPosition().x + rect.getSize().x / 2 - 3, rect.getPosition().y + rect.getSize().y);
}

void Player::moveLeft() {
	rectPlayer.top = 140;
	//if the previous key pressed was right, change the sprite's x-coordinate's starting point
	if (direction == right || rectPlayer.left == 0) {
		rectPlayer.left = 95 * 5;
	}
	if (clock.getElapsedTime().asSeconds() > 0.05f) {
		if (rectPlayer.left == (95 * 3)) {
			rectPlayer.left = 95 * 5;
			pSprite.move(-10, 0);
			rect.move(-10, 0);
		}
		else {
			rectPlayer.left -= 95;
			pSprite.move(-10, 0);
			rect.move(-10, 0);
		}
		pSprite.setTextureRect(rectPlayer);
		clock.restart();
		direction = left;
	}
	//cout << "(" << rectPlayer.top << ", " << rectPlayer.left << ")" << endl;
}
void Player::moveRight() {
	rectPlayer.top = 0;
	//if the previous key pressed was left, change the sprite's x-coordinate's starting point
	if (direction == left || rectPlayer.left == (95 * 5)) {
		rectPlayer.left = 0;
	}
	if (clock.getElapsedTime().asSeconds() > 0.05f) {
		if (rectPlayer.left == (95 * 2)) {
			rectPlayer.left = 0;
			pSprite.move(10, 0);
			rect.move(10, 0);
		}
		else {
			rectPlayer.left += 95;
			pSprite.move(10, 0);
			rect.move(10, 0);
		}
		pSprite.setTextureRect(rectPlayer);
		clock.restart();
	}
	direction = right;
	//cout << "(" << rectPlayer.top << ", " << rectPlayer.left << ")" << endl;
}

void Player::moveDown()
{
	/*rectPlayer.left = 95 * 6;
	pSprite.setTextureRect(rectPlayer);*/
	idle();
	rect.move(0, 1);
	pSprite.move(0, 1);
}

void Player::dead() {
	rectPlayer.top = 140;
	rectPlayer.left = 95 * 6;
	rect.move(0, 1);
	pSprite.move(0, 1);
	pSprite.setTextureRect(rectPlayer);
}
void Player::addCoinCount() {
	coinCount += 1;
}
void Player::idle() {
	if (direction == right) {
		rectPlayer.left = 95 * 5;
	}
	else {
		rectPlayer.left = 0;
	}
	pSprite.setTextureRect(rectPlayer);
}

bool Player::checkIfCoinIsTouched(Coin c)
{
	//Fix getSpriteRect()
	return (pSprite.getGlobalBounds().intersects(c.getSpriteBounds()));
}

void Player::draw(sf::RenderWindow &window)
{
	window.draw(pSprite);
}

//Dario Stuff:

void Player::setPosition(int x, int y)
{
	pSprite.setPosition(x, y + 5);
	rect.setPosition(x, y);
}


int Player::getPositionX()
{
	return pSprite.getPosition().x;

}

int Player::getPositionY()
{
	return pSprite.getPosition().y;

}
void Player::changeJump() {
	if (direction == right) {
		rectPlayer.left = 95 * 4;
		cout << "Direction is right in Change jump function\n";
	}
	else {
		rectPlayer.left = 95;
		cout << "Direction is left in change jump functin\n";
	}
	
	pSprite.setTextureRect(rectPlayer);
	cout << "The sprite has been changed\n";
}

void Player::gravity(float deltaTime)
{
//	cout << "Inside Mario.jump function
	speedValue -= gravityAcceleration * deltaTime;// by this is what makes mario go up in air
	pSprite.move(0, -speedValue);// setting up the sprite value to move accordingly
	rect.move(0, -speedValue);
}

bool Player::checkCollisionTile(Tile p)// check collision with a tile
{


	if (BottomRect.getGlobalBounds().intersects(p.mainRect.getGlobalBounds()))
	{
		if (rect.getGlobalBounds().intersects(p.mainRect.getGlobalBounds()))
		{
			rect.setPosition(rect.getPosition().x, p.mainRect.getPosition().y - 55);
			pSprite.setPosition(rect.getPosition().x, p.mainRect.getPosition().y - 55);
			return true;
		}
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
		rect.setPosition(p.mainRect.getPosition().x + p.mainRect.getSize().x + 10, rect.getPosition().y);
		pSprite.setPosition(p.mainRect.getPosition().x + p.mainRect.getSize().x + 10, rect.getPosition().y);
		return true;
	}
	//cout << "Before Right check if statement\n";
	if (RightRect.getGlobalBounds().intersects(p.mainRect.getGlobalBounds()) && rect.getGlobalBounds().intersects(p.mainRect.getGlobalBounds()))
	{
		rect.setPosition(p.mainRect.getPosition().x - 50, rect.getPosition().y);
		pSprite.setPosition(p.mainRect.getPosition().x - 50, rect.getPosition().y);
		return true;
	}

	//cout<<"No collision in check collision tile\n";
	return false;



}


void Player::checkCollisionEnemy(Enemy& p)// check collision with a tile
{
	if (BottomRect.getGlobalBounds().intersects(p.getMainRect().getGlobalBounds()) && rect.getGlobalBounds().intersects(p.getMainRect().getGlobalBounds()))
	{
		p.setIsDead(true);
		return;
	}
	//cout << "Before Top check if statement\n";

	if (LeftRect.getGlobalBounds().intersects(p.getMainRect().getGlobalBounds()) && rect.getGlobalBounds().intersects(p.getMainRect().getGlobalBounds()))
	{
		//cout << "Goomba Touched Mario from Right\n";
		isAlive = false;
		return;
	}
	//cout << "Before Right check if statement\n";
	if (RightRect.getGlobalBounds().intersects(p.getMainRect().getGlobalBounds()) && rect.getGlobalBounds().intersects(p.getMainRect().getGlobalBounds()))
	{
		//cout << "Gomba touched Mario from Left\n";
		isAlive = false;
		return;
	}

}
