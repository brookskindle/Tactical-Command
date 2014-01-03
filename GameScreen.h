/*
Brooks Kindle
brooks.kindle@wsu.edu

GameScreen.h    -   header file for GameScreen class
*/

#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Tokens.h"
class Player;

class GameScreen {
    public:
        GameScreen();
        ~GameScreen();
        bool loaded() const;
        void playTurn(sf::RenderWindow &window, const Player &hero,
                  const std::vector<Player *> &others) const;
    private:
        sf::Sprite spriteOf(Token ship);
        bool _loaded;
        sf::Texture _ships;
        sf::Texture _background;
};//end GameScreen

#endif
