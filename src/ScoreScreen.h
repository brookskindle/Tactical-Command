/*
Brooks Kindle
brooks.kindle@wsu.edu

ScoreScreen.h   -   header file for ScoreScreen class
*/

#ifndef SCORESCREEN_H
#define SCORESCREEN_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"

/* Screen that the player is presented with upon completion of his game */
class ScoreScreen {
    public:
        enum ExitStatus {
            Failure, Close, Continue
        };
        ScoreScreen();
        bool loaded() const;
        ExitStatus show(sf::RenderWindow &, const std::vector<Player*> &) const;
    private:
        bool _loaded;
        sf::Texture _background;
        sf::Font _font;
};//end ScoreScreen

#endif
