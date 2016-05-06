#include <SFML/Graphics.hpp>
#include "enemy.hpp"
// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
#include <iostream>
using namespace std;
int main()
{
    int i = 0;
    sf::Clock clock;
    Enemy goomba;
    
    sf::RenderWindow Window(sf::VideoMode(800, 450), "Super Mario Bros.");
    
    while (Window.isOpen()){ //the game loop
        sf::Time time = clock.getElapsedTime();
        sf::Event Event; //We need an Event loop to let the user interact with the game.
        //An event can be anything from typing, moving the mouse, etc.
        
        while(Window.pollEvent(Event)){
            if(Event.type == sf::Event::Closed)
                Window.close();
        }
        
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
        goomba.draw(Window);
        Window.display();
    }
    return 0;
}
