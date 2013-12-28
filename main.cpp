/*
Brooks Kindle
brooks.kindle@wsu.edu

main.cpp    -   program start point
*/

#include "Game.h"

int main(void) {
    //sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], Game::GAME_NAME); //uncomment this for linux sides
    sf::RenderWindow window(sf::VideoMode(1000, 500), Game::GAME_NAME);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Sprite ship;
    sf::Texture texture;
    sf::View view = window.getDefaultView();
    if(texture.loadFromFile("space_ship.png")) {
        ship.setTexture(texture);
        ship.setOrigin(ship.getScale().x / 2, ship.getScale().y / 2);
        view.setCenter(ship.getOrigin());
        window.setView(view);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.draw(ship);
        window.display();

        //move the ship slightly
        ship.move(.005, .0025);
        view.setCenter(ship.getPosition());
        window.setView(view);
    }
    return 0;
}//end main