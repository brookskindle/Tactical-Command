/*
Brooks Kindle
brooks.kindle@wsu.edu

PlacementMenu.h -   header file for PlacementMenu class
*/

#ifndef PLACEMENTMENU_H
#define PLACEMENTMENU_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "TokenButton.h"

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
        sf::Sprite spriteOf(Token ship) const;
        void initialize(Player &player);
        void draw(sf::RenderWindow &window);
        void handleClick(sf::RenderWindow &window);

        bool _loaded;
        sf::Texture _background;
        sf::Texture _tokens;
        sf::Texture _highlight;
        std::vector<TokenButton> tokens;
        sf::Sprite background;
};//end PlacementMenu

#endif
