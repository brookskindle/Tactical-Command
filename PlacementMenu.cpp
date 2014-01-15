/*
Brooks Kindle
brooks.kindle@wsu.edu

PlacementMenu.h -   header file for PlacementMenu class
*/

#include "PlacementMenu.h"
#include "util.h"
#include "Game.h"
using std::vector;

/* constructs the placement menu */
PlacementMenu::PlacementMenu() {
    _loaded = _background.loadFromFile("ShipPlacement.png") &&
              _tokens.loadFromFile("TokenSheet.png") &&
              _highlight.loadFromFile("TokenSelection.png");
}//end constructor


/* Returns whether or not the placement menu was loaded */
bool PlacementMenu::loaded() const {
    return _loaded;
}//end loaded


/* Draws the placement menu and allows the user to place the ships
for the given player */
PlacementMenu::MenuAction PlacementMenu::placeShips(sf::RenderWindow &window,
                                                    Player &player) {
    MenuAction action = Failure;
    if(!loaded()) {
        return action;
    }

    //Step 0: initialize variables needed for this method
    sf::Sprite sprite;
    vector<sf::Sprite> sprites;
    sf::Sprite background;
    bool highlighted = false; //no sprite is highlighted yet
    sf::Sprite primaryHighlight,
               secondaryHighlight;
    primaryHighlight.setTexture(_highlight);
    background.setTexture(_background);
    primaryHighlight.setTextureRect(sf::IntRect(0,0,34,30));
    secondaryHighlight.setTextureRect(sf::IntRect(34,0,34,30));

    //Step 1: determine how much we need to scale our sprites
    sf::Vector2f scale;
    scale.x = (float)Game::DEFAULT_WIDTH / _background.getSize().x;
    scale.y = (float)Game::DEFAULT_HEIGHT / _background.getSize().y;
    background.setScale(scale);

    //Step 2: create the sprites
    sf::Vector2i spriteStart;
    sf::FloatRect rect = spriteOf(Token::HitToken).getGlobalBounds();
    spriteStart.x = 341;
    spriteStart.y = 300 - rect.height * 5;
    sf::Vector2f position;
    position.x = spriteStart.x * scale.x;
    position.y = spriteStart.y * scale.y;
    for(int i = 0; i < player.board().rows(); i++) {
        for(int j = 0; j < player.board().columns(); j++) {
            Coordinate c(i, j); //token coordinate
            sprite = spriteOf(player.board()[c]);
            sprite.setScale(scale); //scale the sprite
            sprite.setPosition(position);
            position.x += sprite.getGlobalBounds().width;
            sprites.push_back(sprite);
        }//end for j
        position.y += sprite.getGlobalBounds().height;
        position.x = spriteStart.x * scale.x;
    }//end for i

    //Step 3: Draw to the sprites to the window
    window.clear();
    window.draw(background);
    for(auto s : sprites) {
        window.draw(s);
    }
    if(highlighted) {
        window.draw(primaryHighlight);
    }
    window.display();

    //Step 4: Handle window events 
    bool done = false;
    do {
        sf::Event e;
        while(window.pollEvent(e)) {
            switch(e.type) { //determine what to do based on the window event
                case sf::Event::Closed: //terminate the menu
                    action = Close;
                    done = true;
                    break;
                case sf::Event::MouseButtonPressed: //check for sprite click
                    for(auto s : sprites) {
                        if(util::clicked(s, sf::Mouse::Left, window)) {
                            //TODO: now that a sprite has been clicked, what needs to happen?
                            if(!highlighted) { //sprite isn't highlighted, do it
                                highlighted = true;
                                primaryHighlight.setPosition(s.getPosition());
                            }
                            else {
                                highlighted = false;
                            }
                        }
                    }//end for
                case sf::Event::GainedFocus:
                case sf::Event::Resized: //redraw items to the menu
                    window.clear();
                    window.draw(background);
                    for(auto s : sprites) {
                        window.draw(s);
                    }
                    if(highlighted) {
                        window.draw(primaryHighlight);
                    }
                    window.display();
                    break;
                default: //some other event, but we don't care
                    break;
            }//end switch
        }//end while
    }while(!done);

    return action;
}//end placeShips


/* Returns a sprite of the given ship token */
sf::Sprite PlacementMenu::spriteOf(Token ship) const {
    if(!loaded()) { return sf::Sprite(); }

    sf::Sprite sprite;
    sprite.setTexture(_tokens, true);
    const int spriteWidth = 34,
              spriteHeight= 30;
    sf::IntRect rect;
    rect.top = 0;
    rect.left = 0;
    rect.height = spriteHeight;
    rect.width = spriteWidth;

    /* Determine what texture the sprite has based on its token */
    switch(ship) {
        case DestroyerToken:
        case FrigateToken:
        case CrusaderToken:
        case ValkyrieToken:
        case InterceptorToken:
            rect.left += spriteWidth;
        case MissToken:
            rect.left += spriteWidth;
        case HitToken:
            rect.left += spriteWidth;
        case SpaceToken:
            sprite.setTextureRect(rect);
            break;
    }//end switch

    return sprite;
}//end spriteOf
