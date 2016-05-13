#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include"Player.h"
#include"Coin.h"
#include "enemy.h"
#include<iostream>
using namespace std;

int main()
{
	sf::SoundBuffer clear;
	sf::SoundBuffer coin1;
	sf::SoundBuffer jump1;
	sf::SoundBuffer flag2;
	sf::Sound coinSound;
	sf::Sound jumpSound;
	sf::Sound downFlag;
	sf::Sound stageClear;
	sf::Music music;
	sf::Vector2f screenDimensions(800, 450);// vector to store our screen dimensions
	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "View Port");
	sf::Texture texture;// texture in order
	sf::Texture title;
	sf::Texture flag;
	sf::Sprite Flag1;
	sf::Sprite title1;
	sf::Sprite sprite;
	sf::View view;// we need to be able to move our screen along our game
	sf::Event event;// check for event
					//sf::Mouse mouse;
	int counter = 0;
	Player Mario;// instance of our player

				 //Goomba Part
	int i = 0;//keeps track of how many steps the goomba has taken
	int counterDead = 12; //used to keep trak of how many dead so for loop do not run more than they need to
	Enemy e[12];// create an array for all of the enemy
	e[0].setPosition(850, 375);
	e[1].setPosition(1243, 375);
	e[2].setPosition(1871, 375);
	e[3].setPosition(2036, 375);
	e[4].setPosition(2456, 375);
	e[5].setPosition(7632, 375);
	e[6].setPosition(1098 * 2, 375);
	e[7].setPosition(1574 * 2, 375);
	e[8].setPosition(1907 * 2, 375);
	e[9].setPosition(2096 * 2, 375);
	e[10].setPosition(2579 * 2, 375);
	e[11].setPosition(2700 * 2, 375);

	sf::Clock delta;
	float deltaTime;
	bool whileJump = false;

	//Data dat;
	Coin c[12];// create an array of all of our coins

	c[0].setPosition(257 * 2, 138 * 2);
	c[1].setPosition(354 * 2, 73 * 2);
	c[2].setPosition(339 * 2, 138 * 2);
	c[3].setPosition(370 * 2, 138 * 2);
	c[4].setPosition(1250 * 2, 138 * 2);
	c[5].setPosition(1505 * 2, 73 * 2);
	c[6].setPosition(1697 * 2, 138 * 2);
	c[7].setPosition(1746 * 2, 138 * 2);
	c[8].setPosition(1793 * 2, 138 * 2);
	c[9].setPosition(2066 * 2, 73 * 2);
	c[10].setPosition(2080 * 2, 73 * 2);
	c[11].setPosition(2722 * 2, 138 * 2);

	if (!coin1.loadFromFile("images/coinSound.wav") || !jump1.loadFromFile("images/jumpSound.wav") || !flag2.loadFromFile("images/downFlagpole.wav") || !clear.loadFromFile("images/stageClear.wav"))
		cout << "Could not load sound effects\n";

	if (!music.openFromFile("images/marioSong.ogg"))// import mario theme song
		cout << "Could not load file\n";

	if (!texture.loadFromFile("images/NES2.png") || !title.loadFromFile("images/marioTitle6.png")|| !flag.loadFromFile("images/marioFlag6.png"))// import our background and our main mario page
		cout << "Could not load file\n";

	coinSound.setBuffer(coin1);
	jumpSound.setBuffer(jump1);
	downFlag.setBuffer(flag2);
	stageClear.setBuffer(clear);

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
	title1.setScale(.6, .6);

	Flag1.setTexture(flag);
	Flag1.setScale(.5, .5);
	Flag1.setPosition(3157 * 2, 41 * 2);


	sf::Vector2f position(0, 0);// this vector will keep track of the position of our screen

	view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));// we are assigning our screen start at 0,0, with the same dimensions as our game screen

	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));// position our view at 0, 0, and 1 and 1 represent that we want to view the full screen vertically and horizontally.

	window.setVerticalSyncEnabled(true);

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
	music.play();// start game music as soon as game starts
	while (window.isOpen())// game loop
	{

		deltaTime = delta.restart().asSeconds();
		//cout << "Mario's Position: " << Mario.getPositionX() << endl;
		while (window.pollEvent(event))// check for events
		{
			if (event.type == sf::Event::Closed)// if you would like to close the window
				window.close();

		}

		//*********************************** Mario ***********************************
		if (Mario.getPositionX() >= 3167 * 2)// When Mario reaches the flag
		{
			music.stop();

			downFlag.play();

			while (Flag1.getPosition().y < 345)
			{
				cout << " Mario PositionX: " << Mario.getPositionX() << " Mario PositionY: " << Mario.getPositionY() << endl;
				Flag1.move(0, 2);

				if (Mario.getPositionY() < 345)
					Mario.moveDown();


				window.draw(sprite);// display the background
				window.setView(view);// display the view
				Mario.draw(window);
				window.draw(Flag1);
				window.display();
				window.clear();

			}
			stageClear.play();
			while (Mario.getPositionX() == 3172 * 2 || Mario.getPositionX() <= 3272 * 2)// this loop will run as long as mario has reaches the flag, and the position of mario is less than the position of the entrance of the castle
			{
				//cout << "Here is the flag\n";
				Mario.moveRight();                 //rect.move(2, 0);//* clock.getElapsedTime().asSeconds();// move mario by itself until it reaches the entrance of castle
				//cout << "After supposedly moving the block by itself\n";
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


		if (whileJump)// this is to prevent from jumping again when mario is in the air
			cout << "Mario Jumped" << endl;

		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//if mario is on the ground
			{
				jumpSound.play();
				Mario.speedValue = Mario.getJumpValue() / Mario.getMarioMass();//mario is going to go up this amount of pixels
				whileJump = true;// set whileJump to true knowing its in the air
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))// if right arrow is pressed
		{

			cout << " Mario PositionX: " << Mario.getPositionX() << " Mario PositionY: " << Mario.getPositionY() << endl;
			Mario.moveRight();// move mario


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

		else {
			Mario.idle();
		}

		if (whileJump)// if mario is in the air
		{
			Mario.jump(deltaTime);// start decreasing to bring mario back to ground
			if (Mario.getPlayerSprite().getPosition().y > 345)// if mario is less than the ground
			{
				Mario.getPlayerSprite().setPosition(Mario.getPlayerSprite().getPosition().x, 345);// set mario's position X position to where position he is, and Y position to 345, which is the value where our ground is in our map
				whileJump = false;// set this to false for we are now on the ground

			}
		}
		for (int i = 0; i < 12; i++) {
			if (Mario.checkIfCoinIsTouched(c[i]) && c[i].getIsVisible()) {
				Mario.addCoinCount();
				coinSound.play();
				cout << "Number of Coins: " << Mario.getCoinCount() << endl;
				c[i].setIsVisible(false);
			}
		}
		//***************************************** End Of Mario ***********************************************


		//******************************************** Goomba **************************************************
		for(int j = 0; j < 12; j++){
				if((e[j].isIntersectingX(Mario.getPositionX()))&& (e[j].isIntersectingY(Mario.getPositionY()))){ //checks if enemy is hit by mario
						e[j].setDead(window);
						e[j].setIsDead(true);
						e[j].setIsVisible(false);
				}
		}

		//Moves the enemy either left or right
		for(int j = 0; j < 12 ; j++){
				//cout <<"sprite postion is " << e[j].getSprite().getPosition().x << endl;
				if((e[j].getSprite().getPosition().x > 5000 || (e[j].getDirection() == 0)) && e[j].getSprite().getPosition().x > 0) //move the enemy left. 5000 is the boundary for the right side
						e[j].moveLeft();
				else if(e[j].getSprite().getPosition().x <= 0|| e[j].getDirection() == 1) // moves the enemy right
						e[j].moveRight();
		}
		//***************************************** End Of Goomba ***********************************************

		// disregard this
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
		for (int i = 0; i < 12; i++) {
			if (e[i].getIsVisible() == true)
				e[i].draw(window);
		}
		Mario.draw(window);
		window.draw(Flag1);
		window.display();
		window.clear();
	}//end of game loop


	return 0;
}
