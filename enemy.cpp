#include "enemy.hpp"
#include "ResourcePath.hpp"
#include <iostream>
using namespace std;

Enemy::Enemy(){
   if(!pTexture.loadFromFile("images/enemy.png"))
       cout << "Could not load image from file" << endl;
    rectEnemy.left = 0;
    rectEnemy.top = 0;
    move.left = 0;
    move.top = 0;
    move.width = 250;
    move.height = 248;
    rectEnemy.width = 250;
    rectEnemy.height = 248;
    pSprite.setTexture(pTexture);
    pSprite.setTextureRect(rectEnemy);
    pSprite.setScale(.2,.2);
    direction = right;
}

void Enemy::moveLeft(){
    if(direction == right)
        move.left = 0;
    if(direction == right || rectEnemy.left == 250)
        rectEnemy.left = 250 * 2;
    if (clock.getElapsedTime().asSeconds() > 0.05f) {
        if(rectEnemy.left == 250 * 2){
            rectEnemy.left = 0;
            pSprite.move(-10, 0);
            move.left -=10;
        }else{
            rectEnemy.left += 250;
            pSprite.move(-10,0);
            move.left-=10;
        }
        pSprite.setTextureRect(rectEnemy);
        clock.restart();
        direction = left;
    }
}

void Enemy::moveRight(){
    if(direction == left)
        move.left = 0;
    if(direction == left || rectEnemy.left == 250 * 2)
        rectEnemy.left = 0;
    if (clock.getElapsedTime().asSeconds() > 0.05f){
        if(rectEnemy.left == 250){
            rectEnemy.left = 0;
            pSprite.move(10, 0);
            move.left+=10;
        }else{
            rectEnemy.left += 250;
            pSprite.move(10,0);
            move.left += 10;//not sure exactly where left starts but wokr if done like this
        }
        pSprite.setTextureRect(rectEnemy);
        clock.restart();
        direction = right;
    }
}

void Enemy::setDead(){
    rectEnemy.left = 250 * 3;
}

bool Enemy::isIntersecting(const sf::IntRect& ob1){
    if(move.left == ob1.left)
        return true;
    else
        return false;
}

void Enemy::draw(sf::RenderWindow &window){
    window.draw(pSprite);
}