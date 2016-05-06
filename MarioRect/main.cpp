#include <SFML/Graphics.hpp>
#include "enemy.hpp"
// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
#include <iostream>
using namespace std;

int main(){
    int i = 0;
    sf::Clock clock;
    Enemy goomba;
    sf::IntRect box;
    sf::Texture aT;
    sf::Sprite a;
    if(!aT.loadFromFile(resourcePath()+"images.png"))
        cout << "Could not load image from file" << endl;
    box.left = 400;
    box.top = 0;
    box.width = 300;
    box.height = 248;
    a.setTexture(aT);
    a.setTextureRect(box);
    a.setScale(.4,.4);
    a.move(500,0);//have to mive the sprite 100 more than box
    int j =0;
    sf::RenderWindow Window(sf::VideoMode(800, 450), "Super Mario Bros.");
    
    while (Window.isOpen()){ //the game loop
        sf::Time time = clock.getElapsedTime();
        sf::Event Event; //We need an Event loop to let the user interact with the game.
        //An event can be anything from typing, moving the mouse, etc.
        
        while(Window.pollEvent(Event)){
            if(Event.type == sf::Event::Closed)
                Window.close();
        }
        
        if(goomba.isIntersecting(box) == true){
            cout << "Object Collision" << endl;
            if(goomba.getSprite().getPosition().x >= 400)
                i++;
            else
                i++;
        }
       /* if(goomba.isIntersecting(box) && box.getYlocation > starting location)
        {
            goomba.setDead();
        }*/
        if(i % 2 == 0){
            if(goomba.getSprite().getPosition().x < 800)
                goomba.moveRight();
            else
                i++;
        }
        
        if(i % 2 != 0){
            if(goomba.getSprite().getPosition().x > 0)
                goomba.moveLeft();
            else
                i++;
        }
        clock.restart().asMilliseconds();
        
        //default of display function's default color is black
        Window.clear();
        Window.draw(a);
        goomba.draw(Window);
        Window.display();
    }
    return 0;
}
