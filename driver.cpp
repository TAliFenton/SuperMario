#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Coin.h"
using namespace std;
	
int main() {
	sf::Clock clock;
	Player Mario;
	int x = 350;
	int y = 350;
	Coin c;
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
			else{
				Mario.idle();
			}
			if (Mario.checkIfCoinIsTouched(c) && c.getIsVisible()){
				Mario.addCoinCount();
				cout << "Number of Coins: " << Mario.getCoinCount() << endl;
				c.setIsVisible(false);
			}
		}
		if (Mario.checkIfCoinIsTouched(c) && c.getIsVisible()) {
			Mario.addCoinCount();
			cout << "Number of Coins: " << Mario.getCoinCount() << endl;
			c.setIsVisible(false);
		}
		clock.restart().asMilliseconds();
		Mario.draw(Window);
		c.draw(Window);
		//default of display function's default color is black
		Window.display();
		Window.clear();
	}
	return 0;
}

