/*
Brooks Kindle
brooks.kindle@wsu.edu

GameScreen.cpp    -   source file for GameScreen class
*/

#include "GameScreen.h"
#include "Player.h"
using std::vector;

/* Constructs the game screen */
GameScreen::GameScreen() :_loaded(false) {
    _loaded = _ships.loadFromFile("./TokenSheet.png") &&
              _background.loadFromFile("./GameScreen.png");
}//end constructor


/* Destructs the game screen */
GameScreen::~GameScreen() {
}//end destructor


/* Returns whether or not the game screen is loaded */
bool GameScreen::loaded() const {
    return _loaded;
}//end loaded


/* Displays the game screen to the window and plays the hero's turn.
This means, the hero is allowed to decide which of the other players he wants
to attack. and then does so */
void GameScreen::playTurn(sf::RenderWindow &window, const Player &hero,
                          const vector<Player *> &others) const {
    //TODO: finish this function
}//end playTurn


/* Returns a sprite of the given ship token */
sf::Sprite GameScreen::spriteOf(Token ship) {
    if(!loaded()) { return sf::Sprite(); }

    sf::Sprite sprite;
    sprite.setTexture(_ships, true);
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
