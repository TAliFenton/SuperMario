//
//  enemy.hpp
//  MarioRect
//
//  Created by Ali Fenton on 5/4/16.
//  Copyright © 2016 Ali Fenton. All rights reserved.
//
#pragma once
#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <SFML/Graphics.hpp>
#include <stdio.h>
class Enemy
{
    private:
        sf::Clock clock;
        sf::Texture pTexture;
        sf::IntRect rectPlayer;
        sf::Sprite pSprite;
        enum lastDirectionFacing { up, down, left, right };
        int direction;
    public:
        Enemy();
        void setDead();
        void moveRight();
        void moveLeft();
        void draw(sf::RenderWindow &window);
        sf::Sprite getSprite()const{return pSprite;}
        bool isCollision(int x, int y, int x2, int y2);
    
};

#endif /* enemy_hpp */
