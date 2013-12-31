/*
Brooks Kindle
brooks.kindle@wsu.edu

util.h  -   header file for util namespace
*/

#ifndef UTIL_H
#define UTIL_H

#include <SFML/Graphics.hpp>

/* namespace for utility functions */
namespace util {
    void pressEnterToContinue();
    bool clicked(const sf::Sprite &sprite, sf::Mouse::Button button, 
                 const sf::RenderWindow &relativeTo);
};//end util

#endif
