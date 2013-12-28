/*
Brooks Kindle
brooks.kindle@wsu.edu

main.cpp    -   program start point
*/

#include <vector>
#include <SFML/Graphics.hpp>
using std::vector;

int main(void) {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Sprite ship;
    sf::Texture texture;
    if(texture.loadFromFile("space_ship.png")) {
        ship.setTexture(texture);
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
    }
    return 0;
}//end main