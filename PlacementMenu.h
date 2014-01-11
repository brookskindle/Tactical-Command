/*
Brooks Kindle
brooks.kindle@wsu.edu

PlacementMenu.h -   header file for PlacementMenu class
*/

#ifndef PLACEMENTMENU_H
#define PLACEMENTMENU_H

#include <SFML/Graphics.hpp>
#include "Player.h"

/* GUI menu to allow a given player to place his ships in a convenient way */
class PlacementMenu {
    public:
        enum MenuAction {
            Failure, Close, Continue
        };
        PlacementMenu();
        bool loaded() const;
        MenuAction placeShips(sf::RenderWindow &window, Player &player);
    private:
        bool _loaded;
        sf::Texture _background;
        sf::Texture _tokens;
        sf::Texture _highlight;
};//end PlacementMenu

#endif