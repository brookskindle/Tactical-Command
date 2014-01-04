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
GameScreen::MenuAction GameScreen::playTurn(sf::RenderWindow &window,
                const Player &hero, const vector<Player *> &others) const {
    MenuAction action = Failure;
    if(!loaded()) {
        return action;
    }
    action = Continue;

    //Step 0: create the sprites for our game screen
    struct TokenButton {
        int playerId; //id of the player the token belongs to
        sf::Sprite sprite; //drawable sprite of the token
        Coordinate coord; //coordinate of the token on the player's board
    };
    vector<sf::Sprite> heroSprites; //token sprites for our hero
    vector<TokenButton> otherSprites; //token buttons for the other players

    //create the sprites for our hero first
    sf::Vector2f position;
    position.x = 341.0f;
    position.y = 300.0f;
    for(int i = 0; i < hero.board().rows(); i++) {
        sf::Sprite sprite;
        for(int j = 0; j < hero.board().columns(); j++) {
            Coordinate c(i, j); //token coordinate
            sprite = spriteOf(hero.board()[c]);
            sprite.setPosition(position);
            position.x += sprite.getTextureRect().width;
            heroSprites.push_back(sprite);
        }//end for j
        position.y += sprite.getTextureRect().height;
        position.x = 341.0f;
    }//end for i

    //create the sprites for the others
    int nPlayers = 0; //number of players we've created sprites for
    for(Player *p : others) {
        if(!p) { continue; }

        sf::Vector2f position;
        position.x = 341.0f;
        position.y = 300.0f;
        for(int i = 0; i < hero.board().rows(); i++) {
            sf::Sprite sprite;
            for(int j = 0; j < hero.board().columns(); j++) {
                Coordinate c(i, j); //token coordinate
                sprite = spriteOf(hero.board()[c]);
                sprite.setPosition(position);
                position.x += sprite.getTextureRect().width;
                heroSprites.push_back(sprite);
            }//end for j
            position.y += sprite.getTextureRect().height;
            position.x = 341.0f;
        }//end for i

        nPlayers++;
        if(nPlayers >= 3) { 
            break; //done creating sprites for our players
        }
    }//end for Player *p

    //TODO: finish this function
    //Step 1: draw the sprites to the window
    //Step 2: handle window events that transpire

    return action;
}//end playTurn


/* Returns a sprite of the given ship token */
sf::Sprite GameScreen::spriteOf(Token ship) const {
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
