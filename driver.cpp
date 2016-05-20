#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include"Player.h"
#include"Coin.h"
#include "enemy.h"
#include<vector>
#include<iostream>
#include<cstdlib>
#include"Tile.h"
#include<string>
#include<fstream>
using namespace std;

void mainMenu(sf::RenderWindow& w, sf::Event& e, sf::Sprite& t);
void checkMarioDead(Enemy& e1, Enemy& e2, Enemy& e3, Enemy& e4, Enemy& e5, Enemy& e6, Enemy& e7, Enemy& e8, Enemy& e9, Enemy& e10, Enemy& e11, Enemy& e12, Player& m);
void goombaSetGravity(Enemy& e1, Enemy& e2, Enemy& e3, Enemy& e4, Enemy& e5, Enemy& e6, Enemy& e7, Enemy& e8, Enemy& e9, Enemy& e10, Enemy& e11, Enemy& e12, double time);
void goombaUpdatePosition(Enemy& e1, Enemy& e2, Enemy& e3, Enemy& e4, Enemy& e5, Enemy& e6, Enemy& e7, Enemy& e8, Enemy& e9, Enemy& e10, Enemy& e11, Enemy& e12);
void goombaDisplayScreen(Enemy& e1, Enemy& e2, Enemy& e3, Enemy& e4, Enemy& e5, Enemy& e6, Enemy& e7, Enemy& e8, Enemy& e9, Enemy& e10, Enemy& e11, Enemy& e12, sf::RenderWindow& w);
void gameOver(int lives, sf::Clock c, sf::Text t, sf::Text t2, sf::Text t3, sf::Text t4, sf::Text t5, sf::Text t6, sf::Text t7);
void endGame(sf::RenderWindow& window);
void restartGame(Player& m, sf::View& v, Enemy& e1, Enemy& e2, Enemy& e3, Enemy& e4, Enemy& e5, Enemy& e6, Enemy& e7, Enemy& e8, Enemy& e9, Enemy& e10, Enemy& e11, Enemy& e12, Coin coin[]);

int main()
{

	ifstream input;

	input.open("Text/tilePlacement.txt");

	if (input.fail())
		cout << "error loading file\n";
	vector<Tile>::iterator tileIterator;
	vector<Tile> tileVector;
	sf::SoundBuffer clear;
	sf::SoundBuffer coin1;
	sf::SoundBuffer jump1;
	sf::SoundBuffer flag2;
	sf::SoundBuffer dead;
	sf::Sound coinSound;
	sf::Sound jumpSound;
	sf::Sound downFlag;
	sf::Sound stageClear;
	sf::Sound deadMario;
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
	Player Mario;// instance of our player
	Tile tiles;
	int endPositionOfView;

	//Goomba Part
	int i = 0;//keeps track of how many steps the goomba has taken
	int counterDead = 12; //used to keep trak of how many dead so for loop do not run more than they need to
	Enemy e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12;// create an array for all of the enemy e1;
	e1.setPosition(400 , 375);
	e2.setPosition(639 , 225);
	e3.setPosition(839 , 200);
	e4.setPosition(2550 , 395);
	e5.setPosition(2950 , 395);
	e6.setPosition(7632, 375);
	e7.setPosition(1098 * 2, 375);
	e8.setPosition(1574 * 2, 375);
	e9.setPosition(1907 * 2, 375);
	e10.setPosition(2096 * 2, 375);
	e11.setPosition(2579 * 2, 375);
	e12.setPosition(2700 * 2, 375);

	sf::Clock delta;
	double deltaTime;
	bool whileJump = false;

	sf::RectangleShape tempGridSpriteOutline;
	tempGridSpriteOutline.setOutlineColor(sf::Color::White);
	tempGridSpriteOutline.setOutlineThickness(0.5);
	tempGridSpriteOutline.setFillColor(sf::Color::Transparent);
	tempGridSpriteOutline.setSize(sf::Vector2f(16 * 2, 16 * 2));

	sf::Vector2i tempGridSize(378, 14);


	Coin c[12];// create an array of all of our coins

			   //********************


	c[0].setPosition(257 * 2, 130 * 2);
	c[1].setPosition(354 * 2, 67 * 2);
	c[2].setPosition(339 * 2, 130 * 2);
	c[3].setPosition(370 * 2, 130 * 2);
	c[4].setPosition(1250 * 2, 130 * 2);
	c[5].setPosition(1505 * 2, 67 * 2);
	c[6].setPosition(1697 * 2, 130 * 2);
	c[7].setPosition(1746 * 2, 130 * 2);
	c[8].setPosition(1793 * 2, 130 * 2);
	c[9].setPosition(2066 * 2, 67 * 2);
	c[10].setPosition(2080 * 2, 67 * 2);
	c[11].setPosition(2722 * 2, 130 * 2);
	int counter25 = 0;

	if (!coin1.loadFromFile("images/coinSound.wav") || !jump1.loadFromFile("images/jumpSound.wav") || !dead.loadFromFile("images/MarioDies.wav") || !flag2.loadFromFile("images/downFlagpole.wav") || !clear.loadFromFile("images/stageClear.wav"))
		cout << "Could not load sound effects\n";

	if (!music.openFromFile("images/marioSong.ogg"))// import mario theme song
		cout << "Could not load file\n";

	if (!texture.loadFromFile("images/marioUniverse.png") || !title.loadFromFile("images/marioTitle6.png") || !flag.loadFromFile("images/marioFlag6.png"))// import our background and our main mario page
		cout << "Could not load file\n";

	coinSound.setBuffer(coin1);
	jumpSound.setBuffer(jump1);
	downFlag.setBuffer(flag2);
	stageClear.setBuffer(clear);
	deadMario.setBuffer(dead);
	int counter = 0;//this counter will take input from our text file

	sprite.setTexture(texture);
	sprite.setScale(2, 2);

	title1.setTexture(title);
	title1.setScale(.6, .6);

	Flag1.setTexture(flag);
	Flag1.setScale(.5, .5);
	Flag1.setPosition(3157 * 2, 41 * 2);

	bool collides = true;//checking to see if Mario collides with a block


	sf::Vector2f position(0, 0);// this vector will keep track of the position of our screen

	view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));// we are assigning our screen start at 0,0, with the same dimensions as our game screen

	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));// position our view at 0, 0, and 1 and 1 represent that we want to view the full screen vertically and horizontally.

	window.setVerticalSyncEnabled(true);


	int counter2 = 0;//a counter that acts as our index to check our vector[counter2]

					 //*********************************************************
					 //This scope of code will read in from the file, and at the location x, y if there is a 1 we will place a block, else we will continue
	for (int i = 0; i < tempGridSize.x; i++)
	{
		for (int j = 0; j < tempGridSize.y; j++)
		{
			tempGridSpriteOutline.setPosition(i * tempGridSpriteOutline.getSize().x, j *  tempGridSpriteOutline.getSize().y);

			input >> counter;
			if (counter == 1)
			{
				tiles.setMainRectPosition(i * 32, j * 32);//we are multiplying by 32 because the size of the square is 16 by 16, but since we are scaling it by two we multiply 16 * 2
				tileVector.push_back(tiles);// for every tile that has been placed in our
			}

			else
				continue;


		}

	}

	//*********************************************************

	mainMenu(window, event, title1);// this is for our intro screen

	int score = 0;
	sf::Font MarioFont;
	if (!MarioFont.loadFromFile("images/emulogic.ttf"));
	{
		cout << "Cannot load font\n";
	}
	sf::String sentence1 = "World";
	sf::String sentence2 = "Grit";
	sf::String sentence = "Dario";
	sf::String sentence3 = "Ali";
	sf::String sentence4 = "Nicole";
	sf::Text text4(sentence1, MarioFont, 20);
	sf::Text text5(sentence2, MarioFont, 20);
	sf::Text text(sentence, MarioFont, 20);
	sf::Text text6(sentence3, MarioFont, 20);
	sf::Text text7(sentence4, MarioFont, 20);
	text4.setPosition(360, 0);
	text5.setPosition(360, 29);
	text6.setPosition(560, 0);
	text7.setPosition(560, 29);
	string n = "x0";
	sf::Text text3;
	sf::Text text2;
	text2.setCharacterSize(20);
	text3.setCharacterSize(20);
	text2.setFont(MarioFont);
	text3.setFont(MarioFont);
	text2.setPosition(0, 29);
	text3.setPosition(200, 29);
	text3.setColor(sf::Color::Yellow);

	music.play();// start game music as soon as game starts
	while (window.isOpen())// game loop
	{
		window.setFramerateLimit(200);
	//	cout << "Mario SpeedValue: " << Mario.speedValue << endl;

		endPositionOfView = view.getCenter().x + screenDimensions.x / 2;


		if (Mario.getCoinCount() > 9) {
			n = "x";
		}
		string newScore = to_string(score);
		string coinCount = to_string(Mario.getCoinCount());
		sf::String cCount = n + coinCount;
		sf::String totalScore = newScore;
		text2.setString(totalScore);
		text3.setString(cCount);
		window.draw(sprite);



		counter2 = 0;
		collides = false;// we have this boolean to see if Mario is colliding with a tile
		for (tileIterator = tileVector.begin(); tileIterator != tileVector.end(); tileIterator++)//go through all the tiles in our vector and check if there is collision
		{


			if (Mario.checkCollisionTile(tileVector[counter2]))// check to see if Mario is colliding with a tiles(block) if its true then
			{
				collides = true;// set the collision to true so mario can jump when he intersects with a tile
				Mario.speedValue = 0;// speedValue to zero because Mario  is stanging on the block  so there is no speed Value
			}

			if (e1.checkCollisionTile(tileVector[counter2], endPositionOfView))
				e1.speedValue = 0;

			if (e2.checkCollisionTile(tileVector[counter2], endPositionOfView))
				e2.speedValue = 0;

			if (e3.checkCollisionTile(tileVector[counter2], endPositionOfView))
				e3.speedValue = 0;

			if (e4.checkCollisionTile(tileVector[counter2], endPositionOfView))
				e4.speedValue = 0;

			if (e5.checkCollisionTile(tileVector[counter2], endPositionOfView))
				e5.speedValue = 0;

			if (e6.checkCollisionTile(tileVector[counter2], endPositionOfView))
				e6.speedValue = 0;

			if (e7.checkCollisionTile(tileVector[counter2], endPositionOfView))
				e7.speedValue = 0;

			if (e8.checkCollisionTile(tileVector[counter2], endPositionOfView))
				e8.speedValue = 0;

			if (e9.checkCollisionTile(tileVector[counter2], endPositionOfView))
				e9.speedValue = 0;

			if (e10.checkCollisionTile(tileVector[counter2], endPositionOfView))
				e10.speedValue = 0;

			if (e11.checkCollisionTile(tileVector[counter2], endPositionOfView))
				e11.speedValue = 0;

			if (e12.checkCollisionTile(tileVector[counter2], endPositionOfView))
				e12.speedValue = 0;

			/*if (!Mario.checkCollisionTile(tileVector[counter2]))
			{
				whileJump = true;
			}*/


			counter2++;// increment index so it goes through each of the tiles set up in the game

		}
		//cout << "Mario Speed Value: " << Mario.speedValue << endl;

		/*if (Mario.speedValue  <= 50)// when Mario jumps, and reaches this value in speed value, set while jump to true;
			whileJump = true;*/

		//cout << "While Jump: " << whileJump << endl;

		deltaTime = delta.restart().asSeconds();


		if (Mario.speedValue <= 0 && Mario.speedValue > -2  && collides)// we check speed value to be within this range since speed value depends on the delta time, so when it hits the ground no matter how high Mario goes the speedvalue will always be between that range
																			  //in if statement above, we need to check that collide is true as well so mario is colliding with a block and that he can jump
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//if mario is on the ground
				{
					jumpSound.play();
					Mario.speedValue = Mario.getJumpValue() / Mario.getMarioMass();//mario is going to go up this amount of pixels
					whileJump = true;// set whileJump to true knowing its in the air
				}
			}

		Mario.gravity(deltaTime);// start decreasing to bring mario back to ground
		goombaSetGravity(e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, deltaTime);



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

			while (Flag1.getPosition().y < 182 * 2)// if the position of the flag is less than the position of the floor
			{

				cout << "Inside while loop that brings the flag down\n";
				Flag1.move(0, 2);// move the flag down two pixels at a time

				if (Mario.getPositionY() + 90 < 212  * 2)// if the position of Mario is less than the position of the floor
					Mario.moveDown();// bring mario down


				window.draw(sprite);// display the background
				window.setView(view);// display the view
				Mario.draw(window);
				window.draw(Flag1);
				window.display();
				window.clear();

			}
			stageClear.play();// play the when he clears the stage
			while (Mario.getPositionX() == 3173 * 2 || Mario.getPositionX() <= 3275 * 2)// this loop will run as long as mario has reaches the flag, and the position of mario is less than the position of the entrance of the castle
			{
				cout << "Inside loop where mario moves by itselfs\n";


				//cout << "Here is the flag\n";
				Mario.moveRight();
				counter25++;

				if (counter25 == 10)
					Mario.setPosition(Mario.getPositionX(), Mario.getPositionY() + 25);


				while (Mario.getPositionX() >= 3270 * 2)//once the position of mario is equal to the entrance of the castle then we will draw our terrain and everything except for Mario to simulate that he has gone inside the castle
				{
					while (window.pollEvent(event))// check for events
					{
						if (event.type == sf::Event::Closed)// if you would like to close the window
							window.close();

					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
						return 0;

					cout << "Inside loop where Mario disapperas into castle\n";
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
			Mario.moveRight();//move mario to the right


			if (view.getCenter().x + screenDimensions.x / 2 >= (texture.getSize().x - 5) * 2)// this is to prevent the screen from moving once mario is at the end of our map
				cout << "Its at end of scree\n";

			else if (Mario.getPositionX() + 55 > view.getCenter().x)// if mario passes the center of the screen
			{
				text.setPosition(Mario.getPositionX() + 46 - (screenDimensions.x / 2), 0);
				text2.setPosition(Mario.getPositionX() + 46 - (screenDimensions.x / 2), 29);
				text3.setPosition(Mario.getPositionX() + 46 - (screenDimensions.x / 2) + 200, 29);
				text4.setPosition(Mario.getPositionX() + 46 - (screenDimensions.x / 2) + 360, 0);
				text5.setPosition(Mario.getPositionX() + 46 - (screenDimensions.x / 2) + 360, 29);
				text6.setPosition(Mario.getPositionX() + 46 - (screenDimensions.x / 2) + 560, 0);
				text7.setPosition(Mario.getPositionX() + 46 - (screenDimensions.x / 2) + 560, 29);
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
		for (int i = 0; i < 12; i++) {
			if (Mario.checkIfCoinIsTouched(c[i]) && c[i].getIsVisible()) {
				Mario.addCoinCount();
				coinSound.play();
				cout << "Number of Coins: " << Mario.getCoinCount() << endl;
				score += 200;
				c[i].setIsVisible(false);
			}
		}

		cout << "Mario Speed Value: " << Mario.speedValue << endl;
		cout << "Mario Position Y: " << Mario.getPositionY() << endl;

		if (Mario.getPositionY() > 400)
			Mario.setPosition(Mario.getPositionX(), 350);

		Mario.update();
		goombaUpdatePosition(e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12);
		checkMarioDead(e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, Mario);
		if(!Mario.getIsAlive()){
			if (Mario.decreasePlayerLives()) {
				sf::Clock clock;
				gameOver(Mario.getPlayerLives(), clock, text, text2, text3, text4, text5, text6, text7);
				clock.restart();
				restartGame(Mario, view, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, c);
			}
			else {
				sf::Clock clock;
				gameOver(Mario.getPlayerLives(), clock, text, text2, text3, text4, text5, text6, text7);
				window.close();
				//Call the ending screen and if the user picks continue then call restart. Otherwise, exit the game.
			}
		}
	//***************************************** End Of Mario ***********************************************



		window.setView(view);
		Mario.draw(window);
		for (int i = 0; i < 12; i++)
			c[i].draw(window);

		goombaDisplayScreen(e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, window);
		Mario.draw(window);
		window.draw(text6);
		window.draw(text7);
		window.draw(text5);
		window.draw(text4);
		window.draw(text2);
		window.draw(text);
		window.draw(text3);
		window.draw(Flag1);
		window.draw(Mario.BottomRect);
		window.draw(Mario.getMarioRect());
		window.display();
		window.clear();
	}//end of game loop

	return 0;
}



void mainMenu(sf::RenderWindow& w, sf::Event& e, sf::Sprite& t)
{
	while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)))// intro screen
	{

		while (w.pollEvent(e))// check for events
		{
			if (e.type == sf::Event::Closed)// if you would like to close the window
				w.close();

		}
		w.draw(t);
		w.display();
		w.clear();

	}

}

void checkMarioDead(Enemy& e1, Enemy& e2, Enemy& e3, Enemy& e4, Enemy& e5, Enemy& e6, Enemy& e7, Enemy& e8, Enemy& e9, Enemy& e10, Enemy& e11, Enemy& e12, Player& m)
{

	m.checkCollisionEnemy(e1);
	m.checkCollisionEnemy(e2);
	m.checkCollisionEnemy(e3);
	m.checkCollisionEnemy(e4);
	m.checkCollisionEnemy(e5);
	m.checkCollisionEnemy(e6);
	m.checkCollisionEnemy(e7);
	m.checkCollisionEnemy(e8);
	m.checkCollisionEnemy(e9);
	m.checkCollisionEnemy(e10);
	m.checkCollisionEnemy(e11);
	m.checkCollisionEnemy(e12);

}

void goombaSetGravity(Enemy& e1, Enemy& e2, Enemy& e3, Enemy& e4, Enemy& e5, Enemy& e6, Enemy& e7, Enemy& e8, Enemy& e9, Enemy& e10, Enemy& e11, Enemy& e12, double time)
{
	e1.gravity(time);
	e2.gravity(time);
	e3.gravity(time);
	e4.gravity(time);
	e5.gravity(time);
	e6.gravity(time);
	e7.gravity(time);
	e8.gravity(time);
	e9.gravity(time);
	e10.gravity(time);
	e11.gravity(time);
	e12.gravity(time);
}

void goombaUpdatePosition(Enemy& e1, Enemy& e2, Enemy& e3, Enemy& e4, Enemy& e5, Enemy& e6, Enemy& e7, Enemy& e8, Enemy& e9, Enemy& e10, Enemy& e11, Enemy& e12)
{

	e1.update();
	e2.update();
	e3.update();
	e4.update();
	e5.update();
	e6.update();
	e7.update();
	e8.update();
	e9.update();
	e10.update();
	e11.update();
	e12.update();

}

;
void goombaDisplayScreen(Enemy& e1, Enemy& e2, Enemy& e3, Enemy& e4, Enemy& e5, Enemy& e6, Enemy& e7, Enemy& e8, Enemy& e9, Enemy& e10, Enemy& e11, Enemy& e12, sf::RenderWindow& w)
{
	if (e1.getIsVisible())
		e1.draw(w);

	if (e2.getIsVisible())
		e2.draw(w);

	if (e3.getIsVisible())
		e3.draw(w);

	if (e4.getIsVisible())
		e4.draw(w);

	if (e5.getIsVisible())
		e5.draw(w);

	if (e6.getIsVisible())
		e6.draw(w);

	if (e7.getIsVisible())
		e7.draw(w);

	if (e8.getIsVisible())
		e8.draw(w);

	if (e9.getIsVisible())
		e9.draw(w);

	if (e10.getIsVisible())
		e10.draw(w);

	if (e11.getIsVisible())
		e11.draw(w);

	if (e12.getIsVisible())
		e12.draw(w);

}

void gameOver(int lives, sf::Clock c, sf::Text t, sf::Text t2, sf::Text t3, sf::Text t4, sf::Text t5, sf::Text t6, sf::Text t7) {
	sf::Font MarioFont;
	if (!MarioFont.loadFromFile("images/emulogic.ttf"))
		cout << "Cannot load font\n";
	sf::Texture sTexture;
	sf::Texture nTexture;
	sf::Sprite sSprite;
	sf::Sprite nSprite;
	t.setPosition(0, 0);
	t2.setPosition(0, 29);
	t3.setPosition(200, 29);
	t4.setPosition(360, 0);
	t5.setPosition(360, 29);
	t6.setPosition(560, 0);
	t7.setPosition(560, 29);
	if (!sTexture.loadFromFile("images/mushroom.png"))
		cout << "The player sprite cannot be loaded.\n";
	if(!nTexture.loadFromFile("images/nelson.png"))
		cout << "The Nelson sprite cannot be loaded.\n";
	sSprite.setScale(0.1, 0.1);
	nSprite.setScale(.7, .7);
	sSprite.setTexture(sTexture);
	nSprite.setTexture(nTexture);
	sSprite.setPosition(298, 200);
	nSprite.setPosition(520, 200);
	sf::String lifeCount = to_string(lives);
	sf::String end = "GAME OVER";
	sf::Text x('x', MarioFont, 20);
	sf::Text livesLeft(lifeCount, MarioFont, 20);
	sf::Text gameover(end, MarioFont, 30);
	x.setPosition(366, 225);
	livesLeft.setPosition(410, 225);
	gameover.setPosition(250, 225);
	sf::RenderWindow w(sf::VideoMode(800, 450), "SFML window");

	while (c.getElapsedTime().asSeconds() < 3) {
		w.draw(t);
		w.draw(t2);
		w.draw(t3);
		w.draw(t4);
		w.draw(t5);
		w.draw(t6);
		w.draw(t7);
		cout << c.getElapsedTime().asSeconds() << endl;

		if (lives > 0) {
			w.draw(sSprite);
			w.draw(x);
			w.draw(livesLeft);
		}
		else {
			w.draw(gameover);
			w.draw(nSprite);
		}
		w.display();
	}
	w.close();
}

void endGame(sf::RenderWindow& window) {
	window.clear();
	sf::Font MarioFont;
	if (!MarioFont.loadFromFile("images/emulogic.ttf"))
		cout << "Cannot load font\n";
	sf::Text con("Play", MarioFont, 40);
	sf::Text quit("Quit", MarioFont, 40);
	con.setPosition(450, 200);
	quit.setPosition(450, 500);
	while(true){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			con.setColor(sf::Color::Red);
			quit.setColor(sf::Color::White);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			con.setColor(sf::Color::White);
			quit.setColor(sf::Color::Red);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
			if (con.getColor() == sf::Color::Red)
				false;
				//or we can do:
				//return;
			else
				window.close();
		}
	}
	window.display();
}

void restartGame(Player& m, sf::View& v, Enemy& e1, Enemy& e2, Enemy& e3, Enemy& e4, Enemy& e5, Enemy& e6, Enemy& e7, Enemy& e8, Enemy& e9, Enemy& e10, Enemy& e11, Enemy& e12, Coin coin[])
{
	
	e1.setIsDead(false);
	e1.speedValue = 20;

	e2.setIsDead(false);
	e2.speedValue = 20;

	e3.setIsDead(false);
	e3.speedValue = 20;

	e4.setIsDead(false);
	e4.speedValue = 20;

	e5.setIsDead(false);
	e5.speedValue = 20;

	e6.setIsDead(false);
	e6.speedValue = 20;

	e7.setIsDead(false);
	e7.speedValue = 20;

	e8.setIsDead(false);
	e8.speedValue = 20;

	e9.setIsDead(false);
	e9.speedValue = 20;

	e10.setIsDead(false);
	e10.speedValue = 20;

	e11.setIsDead(false);
	e11.speedValue = 20;

	e12.setIsDead(false);
	e12.speedValue = 20;

	e1.setIsVisible(true);
	e2.setIsVisible(true);
	e3.setIsVisible(true);
	e4.setIsVisible(true);
	e5.setIsVisible(true);
	e6.setIsVisible(true);
	e7.setIsVisible(true);
	e8.setIsVisible(true);
	e9.setIsVisible(true);
	e10.setIsVisible(true);
	e11.setIsVisible(true);
	e12.setIsVisible(true);
	e1.setPosition(400, 375);
	e2.setPosition(639, 225);
	e3.setPosition(839, 200);
	e4.setPosition(2550, 395);
	e5.setPosition(2950, 395);
	e6.setPosition(7632, 375);
	e7.setPosition(1098 * 2, 375);
	e8.setPosition(1574 * 2, 375);
	e9.setPosition(1907 * 2, 375);
	e10.setPosition(2096 * 2, 375);
	e11.setPosition(2579 * 2, 375);
	e12.setPosition(2700 * 2, 375);
	goombaUpdatePosition(e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12);
	coin[0].setPosition(257 * 2, 130 * 2);
	coin[1].setPosition(354 * 2, 67 * 2);
	coin[2].setPosition(339 * 2, 130 * 2);
	coin[3].setPosition(370 * 2, 130 * 2);
	coin[4].setPosition(1250 * 2, 130 * 2);
	coin[5].setPosition(1505 * 2, 67 * 2);
	coin[6].setPosition(1697 * 2, 130 * 2);
	coin[7].setPosition(1746 * 2, 130 * 2);
	coin[8].setPosition(1793 * 2, 130 * 2);
	coin[9].setPosition(2066 * 2, 67 * 2);
	coin[10].setPosition(2080 * 2, 67 * 2);
	coin[11].setPosition(2722 * 2, 130 * 2);
	
	v.reset(sf::FloatRect(0, 0, 800, 450));// we are assigning our screen start at 0,0, with the same dimensions as our game screen

	v.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));// position our view at 0, 0, and 1 and 1 represent that we want to view the full screen vertically and horizontally.
	m.setIsAlive(true);
	m.setPosition(5, 340);
}