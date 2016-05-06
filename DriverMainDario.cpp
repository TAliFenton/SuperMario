#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include<iostream>
#include "Coin.h"
#include"Player.h"
using namespace std;

int main()
{
	
	
	sf::Music music;
	sf::Vector2f screenDimensions(800, 450);// vector to store our screen dimensions
	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "View Port");
	sf::Texture texture;// texture in order
	sf::Texture title;
	sf::Sprite title1;
	sf::Sprite sprite;
	sf::View view;// we need to be able to move our screen along our game
	sf::Event event;// check for event
	//sf::Mouse mouse;
	int counter = 0;
	Player Mario;// instance of our player
	Coin c[12];// create an array of all of our coints

	c[0].setPosition(257 * 2, 138 * 2);
	c[1].setPosition(354 * 2, 73 * 2);
	c[2].setPosition(339 * 2, 138 * 2);
	c[3].setPosition(370* 2, 138 * 2);
	c[4].setPosition(1250 * 2, 138 * 2);
	c[5].setPosition(1505 * 2, 73 * 2);
	c[6].setPosition(1697 * 2, 138 * 2);
	c[7].setPosition(1746 * 2, 138 * 2);
	c[8].setPosition(1793 * 2, 138 * 2);
	c[9].setPosition(2066 * 2, 73 * 2);
	c[10].setPosition(2080 * 2, 73 * 2);
	c[11].setPosition(2722 * 2, 138 * 2);

	if (!music.openFromFile("images/marioSong.ogg"))// import mario theme song
		cout << "Could not load file\n";

	if (!texture.loadFromFile("images/NES2.png")|| !title.loadFromFile("images/marioTitle6.png"))// import our background and our main mario page
		cout << "Could not load file\n";
	/*
	sf::RectangleShape rect(sf::Vector2f(40, 40));
	rect.setFillColor(sf::Color::Red);

	sf::RectangleShape rect2(sf::Vector2f(40, 40));
	rect2.setFillColor(sf::Color::Blue);

	sf::RectangleShape rect3(sf::Vector2f(40, 40));
	rect3.setFillColor(sf::Color::Black);

	rect2.setPosition(600 * 2, 0);
	rect3.setPosition( 690 * 2, 0);*/

	sprite.setTexture(texture);
	sprite.setScale(2, 2.0);

	title1.setTexture(title);
	title1.setScale(.6,.6);

	sf::Vector2f position(0,0);// this vector will keep track of the position of our screen

	view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));// we are assigning our screen start at 0,0, with the same dimensions as our game screen

	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));// position our view at 0, 0, and 1 and 1 represent that we want to view the full screen vertically and horizontally.

	while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)))// intro screen 
	{

		while (window.pollEvent(event))// check for events
		{
			if (event.type == sf::Event::Closed)// if you would like to close the window
				window.close();

		}
		window.draw(title1);
		window.display();
		window.clear();

	}
	
		//music.play();// start game music as soon as game starts
		while (window.isOpen())// game loop
		{

			while (window.pollEvent(event))// check for events
			{
				if (event.type == sf::Event::Closed)// if you would like to close the window
					window.close();

			}
		
				if (Mario.getPositionX() >= 3172 * 2 )// When Mario reaches the flag
				{
					while (Mario.getPositionX() == 3172 * 2 || Mario.getPositionX() <= 3272 * 2)// this loop will run as long as mario has reaches the flag, and the position of mario is less than the position of the entrance of the castle
					{
						cout << "Here is the flag\n";
						Mario.moveRight();                 //rect.move(2, 0);//* clock.getElapsedTime().asSeconds();// move mario by itself until it reaches the entrance of castle
						cout << "After supposedly moving the block by itself\n";
						while (Mario.getPositionX() >= 3270 * 2)//once the position of mario is equal to the entrance of the castle then we will draw our terrain and everything except for Mario to simulate that he has gone inside the castle
						{
							while (window.pollEvent(event))// check for events
							{
								if (event.type == sf::Event::Closed)// if you would like to close the window
									window.close();

							}

							window.draw(sprite);// display the background
							window.setView(view);// display the view
							window.display();
							window.clear();


						}

						window.setView(view);// display the view
						window.draw(sprite);//the background
						Mario.draw(window);//rect
						window.display();
						window.clear();
					}

				}
			


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))// if right arrow is pressed
			{	
				Mario.moveRight();// move mario in a speed of 2


				if (view.getCenter().x + screenDimensions.x / 2 >= (texture.getSize().x - 5) * 2)// this is to prevent the screen from moving once mario is at the end of our map
					cout << "Its at end of scree\n";

				else if (Mario.getPositionX() + 46 > view.getCenter().x)// if mario passes the center of the screen
				{
					position.x = Mario.getPositionX() + 46 - (screenDimensions.x / 2);// we are goin to assign the position.x of our view to the difference of position of Mario and  the screen dimension; 

					view.reset(sf::FloatRect(position.x, position.y, screenDimensions.x, screenDimensions.y));// we are going to reset our view and since position.x is the only one that changed, it will allow our screen to move in the game
				}

				else//if the position of mario is less than the center of view, assign position.x to zero, that way Mario can go back and the view will not move.
				{
					position.x = 0;
				}
	

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				cout << "Screen Position: " << view.getCenter().x - screenDimensions.x / 2 << endl;
				cout << "Mario Position:" << Mario.getPositionX() << endl;
				if (Mario.getPositionX() <= (view.getCenter().x - screenDimensions.x / 2))// if the position of mario is less than left side of the screen; this is to prevent for the player to go back in the game past the screen
				{
					Mario.moveRight();// we are going to add by a speed of 2
					Mario.moveLeft();// we are going to subrtract by 2 which will allow for mario to stay in the same spot because (2 -2 == 
				}// and as soon as the if statement excutes

				Mario.moveLeft();// we are going to subrtract by 2 which will allow for mario to stay in the same spot because (2 -2 == 
			}
			// this regard this
			/*if (Mario.getPositionX() < view.getCenter().x + screenDimensions.x / 2)// as soon as our gombas appear, we are going to make them move towards the left of the screen
			{
				rect2.move(-.1, 0);
			}

			if (rect3.getPosition().x < view.getCenter().x + screenDimensions.x / 2)// same thing as the if statement from above
			{
				if (counter != 60 * 2)// im still working on this part, that way the gomba goes back and fourth in between two tubes
				{
					rect3.move(-1, 0);
					counter++;

				}

				else
				{
					if (rect3.getPosition().x == 639 * 2)
						rect3.move(1, 0);

					if (rect3.getPosition().x == 739 * 2)
						rect3.move(-1, 0);
				}

			}*/
			// display our view and all of our things
			window.setView(view);
			window.draw(sprite);
			Mario.draw(window);
			for (int i = 0; i < 12; i++)
				c[i].draw(window);
			Mario.draw(window);
			window.display();
			window.clear();
	}//end of game loop


	return 0;
}