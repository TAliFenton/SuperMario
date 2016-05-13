#include "enemy.hpp"
#include <iostream>
#include <cmath>
using namespace std;

Enemy::Enemy(){
   if(!pTexture.loadFromFile("images/enemy.png")
       cout << "Could not load image from file" << endl;
    rectEnemy.left = 0;
    rectEnemy.top = 0;
    isVisible = true;
    move.left = 0;
    move.top = 0;
    move.width = 250;
    move.height = 248;
    rectEnemy.width = 250;
    rectEnemy.height = 248;
    pSprite.setTexture(pTexture);
    pSprite.setTextureRect(rectEnemy);
    pSprite.setScale(.1,.1);

    //pSprite.move(30,375);
    direction = left;
    isDead = false;
}

void Enemy::moveLeft(){
    if(isDead == false){
        if(direction == right)
            move.left = 0;
        if(direction == right || rectEnemy.left == 250)
            rectEnemy.left = 250 * 2;
        if (clock.getElapsedTime().asSeconds() > 0.10f){
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
    }else
        pSprite.move(-300, 400);
}

void Enemy::moveRight(){
    if(isDead == false){
        if(direction == left)
            move.left = 0;
        if(direction == left || rectEnemy.left == 250 * 2)
            rectEnemy.left = 0;
        if (clock.getElapsedTime().asSeconds() > 0.10f){
            if(rectEnemy.left == 250){
                rectEnemy.left = 0;
                pSprite.move(10, 0);
                move.left+=10;
            }else{
                rectEnemy.left += 250;
                pSprite.move(10, 0);
                move.left += 10;//not sure exactly where left starts but wokr if done like this
            }
            pSprite.setTextureRect(rectEnemy);
            clock.restart();
            direction = right;
        }
    }else{
        pSprite.move(-300, 400);
    }
}

void Enemy::setPosition(float x, float y){
    pSprite.move(0,0);
    pSprite.setPosition(x,y);

}


//****************************** Player Intersecting with Goomba **************************

void Enemy::setDead(sf::RenderWindow& Window){
    rectEnemy.left = 255 * 2; //sets the enemy to the died image
    pSprite.setTextureRect(rectEnemy); //set texture to die
    Window.clear();
    Window.draw(pSprite);
    Window.display();

}

//If the enemy is still visible
void Enemy::setIsVisible(bool vis){
    isVisible = vis;
}

//Making sure that the intersection when it is intersected with the X axis it enemy does not die
bool Enemy::isIntersectingX(const float ob1){
    if(abs(pSprite.getPosition().x - ob1) <= 43) //sets the range for width which mario can hit
        return true;
    else
        return false;
}

//The Intersection with the Y is greater than enemy hieght and if so the goomba will die
bool Enemy::isIntersectingY(const float ob1Y){
    cout << "******************" <<endl;
    cout << "This is y: "<<pSprite.getPosition().y << " " << "This is x: " << ob1Y << endl;
    cout << "******************" <<endl;
    if((pSprite.getPosition().y - ob1Y) > 40 && (pSprite.getPosition().y - ob1Y) < 45) //sets the height at which the goomba kills mario
        return true;
    else
        return false;
}
//*************************************************************************************

void Enemy::draw(sf::RenderWindow &window){
    window.draw(pSprite);
}
