/*
Brooks Kindle
brooks.kindle@wsu.edu

main.cpp    -   program start point
*/

#include "Game.h"

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
void testSFML();

int main(void) {
    //testSFML();
    Game::start();
    return 0;
}//end main

void testSFML() {
    sf::RenderWindow window(sf::VideoMode(1000, 500), Game::GAME_NAME);
    cout << sf::VideoMode::getFullscreenModes()[0].width << endl;
    cout << sf::VideoMode::getFullscreenModes()[0].height << endl;
    window.setFramerateLimit(30);
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }//end while poll event
        window.clear();
        window.display();
    }//end while is open
}//end testSFML
