/*
Brooks Kindle
brooks.kindle@wsu.edu

util.h  -   header file for util namespace
*/

#ifndef UTIL_H
#define UTIL_H

#include <SFML/Graphics.hpp>
#include "Board.h"

/* namespace for utility functions */
namespace util {
    void pressEnterToContinue();
    bool clicked(const sf::Sprite &sprite, sf::Mouse::Button button, 
                 const sf::RenderWindow &relativeTo);
    bool clicked(const sf::Text &text, sf::Mouse::Button button, 
                 const sf::RenderWindow &relativeTo);
    bool placeRandom(Board &board, Token ship);
    bool placeAllShipsRandomly(Board &board);
};//end util

#endif
