#pragma once
#ifndef TILE_H
#define TILE_H
#include "SFML/Graphics.hpp"
//#include"Player.h"
#include<iostream>
using namespace std;

class Tile
{
public:

	sf::RectangleShape mainRect;


	Tile();

	int mainRectPositionX() const { return mainRect.getPosition().x; }
	int mainRectPositionY() const { return mainRect.getPosition().y; }
	int mainRectSizeX() const { return mainRect.getSize().x; }
	int mainRectSizeY() const { return mainRect.getSize().y; }


	void setMainRectPosition(int x, int y);

};

#endif // !TILE.H