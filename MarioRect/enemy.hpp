#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <SFML/Graphics.hpp>
#include <stdio.h>
class Enemy{
    private:
        sf::Clock clock;
        sf::Texture pTexture;
        sf::IntRect rectEnemy;
        sf::IntRect move;//This rectangle will stay behind the sprite creating a new rectangle
        sf::Sprite pSprite;
        enum lastDirectionFacing {left, right};
        int direction;
    public:
        Enemy();
        void setDead();
        void moveRight();
        void moveLeft();
        void draw(sf::RenderWindow &window);
        sf::Sprite getSprite()const{return pSprite;}
        sf::IntRect getRect()const{return rectEnemy;}
        bool isIntersecting(const sf::IntRect & op1);
    
};

#endif /* enemy_hpp */
