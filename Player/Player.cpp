#include "Player.h"
#include <iostream>
using namespace std;

Player::Player()
{
	if (!pTexture.loadFromFile("MarioMoves.png"))
		cout << "The player sprite cannot be loaded.\n";
	//IntRect objects hold 4 parameters: (Left/x-coordinate, Top/y-coordinate, Width, Height)
	rectPlayer.left = 0;
	rectPlayer.top = 0;
	rectPlayer.width = 95;
	rectPlayer.height = 142;
	pSprite.setTexture(pTexture);
	pSprite.setTextureRect(rectPlayer);
	//I added "playerImage.move(0, 350);" because I want to have Mario start at those specific coordinates [0, 350] instead of having it at the default which is (0, 0) [the upper left corner of the window]
	pSprite.move(0, 350);
	pSprite.setScale(.4, .4);
	direction = right;
	isAlive = true;
	playerLives = 3;
	coinCount = 0;
}

Player::~Player()
{

}

void Player::moveLeft() {
	rectPlayer.top = 142;
	//if the previous key pressed was right, change the sprite's x-coordinate's starting point
	if (direction == right || rectPlayer.left == 0) {
		rectPlayer.left = 95 * 5;
	}
	if (clock.getElapsedTime().asSeconds() > 0.05f) {
		if (rectPlayer.left == (95 * 3)) {
			rectPlayer.left = 95 * 5;
			pSprite.move(-10, 0);
		}
		else {
			rectPlayer.left -= 95;
			pSprite.move(-10, 0);
		}
		pSprite.setTextureRect(rectPlayer);
		clock.restart();
		direction = left;
	}
	cout << "(" << rectPlayer.top << ", " << rectPlayer.left << ")" << endl;
}
void Player::moveRight() {
	rectPlayer.top = 0;
	//if the previous key pressed was left, change the sprite's x-coordinate's starting point
	if (direction == left || rectPlayer.left == (95*5)) {
		rectPlayer.left = 0;
	}
	if (clock.getElapsedTime().asSeconds() > 0.05f) {
		if (rectPlayer.left == (95 * 2)) {
			rectPlayer.left = 0;
			pSprite.move(10, 0);
		}
		else {
			rectPlayer.left += 95;
			pSprite.move(10, 0);
		}
		pSprite.setTextureRect(rectPlayer);
		clock.restart();
	}
	direction = right;
	cout << "(" << rectPlayer.top << ", " << rectPlayer.left << ")" << endl;
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

void Player::draw(sf::RenderWindow &window) 
{
	window.draw(pSprite);
}