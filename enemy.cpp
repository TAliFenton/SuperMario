#include "enemy.hpp"
#include "ResourcePath.hpp"
#include <iostream>
using namespace std;

Enemy::Enemy(){
   if(!pTexture.loadFromFile("images/enemy.png"))
       cout << "Could not load image from file" << endl;
    rectPlayer.left = 0;
    rectPlayer.top = 0;
    rectPlayer.width = 250;
    rectPlayer.height = 248;
    pSprite.setTexture(pTexture);
    pSprite.setTextureRect(rectPlayer);
    pSprite.setScale(.4,.4);
    direction = right;
}

void Enemy::moveLeft(){
    if(direction == right || rectPlayer.left == 250)
        rectPlayer.left = 250 * 2;
    if (clock.getElapsedTime().asSeconds() > 0.05f) {
        if(rectPlayer.left == 250 * 2){
            rectPlayer.left = 0;
            pSprite.move(-10, 0);
        }else{
            rectPlayer.left += 250;
            pSprite.move(-10,0);
        }
        pSprite.setTextureRect(rectPlayer);
        clock.restart();
        direction = left;
    }
}

void Enemy::moveRight(){
    if(direction == left || rectPlayer.left == 250*2)
        rectPlayer.left =0;
    if (clock.getElapsedTime().asSeconds() > 0.05f) {
        if(rectPlayer.left == 250){
            rectPlayer.left = 0;
            pSprite.move(10, 0);
        }else{
            rectPlayer.left += 250;
            pSprite.move(10,0);
        }
        pSprite.setTextureRect(rectPlayer);
        clock.restart();
        direction = right;
    }
}

void Enemy::draw(sf::RenderWindow &window){
    window.draw(pSprite);
}
