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
        enum HighlightType {
            None, Secondary, Primary
        };
        struct HighlightButton {
            TokenButton button;
            HighlightType highlightType;
        };

        sf::Sprite spriteOf(Token ship) const;
        bool done() const;
        void highlightAll(HighlightType type);
        void initialize(Player &player);
        void draw(sf::RenderWindow &window);
        void handleClick(sf::RenderWindow &window, Player &player);
        void highlight(Token ship);

        bool _loaded;
        int _nShipsPlaced;
        bool _highlighted;
        sf::Texture _background;
        sf::Texture _tokens;
        sf::Texture _highlight;
        std::vector<HighlightButton> tokens;
        std::vector<sf::Sprite> highlights;
        sf::Sprite background;
};//end PlacementMenu

#endif
