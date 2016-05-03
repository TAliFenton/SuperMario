#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Coin.h"
using namespace std;
/*
bool Collision(Coin p) {
if (right < p.left || left > p.right || top > p.bottom || bottom < p.top)
return false;
return true;
}
bool Collision(Enemy p) {
if (right < p.left || left > p.right || top > p.bottom || bottom < p.top)
return false;
return true;
}
*/
int main() {
	sf::Clock clock;
	Player Mario;
	int x = 350;
	int y = 350;
	Coin c[10];
	for (int i = 1; i < 10; i++)
		c[i].setPosition(x + (5 * i), y);
	//RenderWindow class can take in a lot of parameters. The following are explanations of what each arguments mean:
	//VideoMode displays a window. It takes in width and height as parameters
	sf::RenderWindow Window(sf::VideoMode(800, 450), "Super Mario Bros.");
	while (Window.isOpen()) //the game loop
	{
		sf::Time time = clock.getElapsedTime();
		sf::Event Event; //We need an Event loop to let the user interact with the game. 
						 //An event can be anything from typing, moving the mouse, etc.

		while (Window.pollEvent(Event)) //while an event is detected, run this loop.
		{
			if (sf::Event::Closed) { //if they click the |x| button, close the window.
				Window.close();
				break;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				Mario.moveRight();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				Mario.moveLeft();
			}
			else {
				Mario.idle();
			}
		}
		clock.restart().asMilliseconds();
		Mario.draw(Window);
		for (int i = 0; i < 10; i++) {
			c[i].draw(Window);
		}
		//default of display function's default color is black
		Window.display();
		Window.clear();
	}
	return 0;
}

