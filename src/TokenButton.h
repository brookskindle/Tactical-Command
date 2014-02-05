/*
Brooks Kindle
brooks.kindle@wsu.edu

TokenButton.h   -   header file for TokenButton class
*/

#ifndef TOKENBUTTON_H
#define TOKENBUTTON_H

#include <SFML/Graphics.hpp>
#include "Coordinate.h"

/* Represents a drawable ship token that represents a
specific token on a player's game board */
struct TokenButton {
    int playerId; //id of the player the token belongs to
    sf::Sprite sprite; //drawable sprite of the token
    Coordinate coord; //coordinate of the token on the player's board
    TokenButton(int pId, sf::Sprite spr, Coordinate c):playerId(pId),
        sprite(spr), coord(c) {}
    TokenButton():playerId(0), coord(0,0) {}
};

#endif
