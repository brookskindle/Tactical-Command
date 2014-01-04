/*
Brooks Kindle
brooks.kindle@wsu.edu

GameScreen.cpp    -   source file for GameScreen class
*/

#include "GameScreen.h"
#include "Player.h"
#include "util.h"
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

        TokenButton button;
        button.playerId = p->id();

        sf::Vector2f position;
        int startX = 0;
        int startY = 0;
        //determine the starting coordinate of the sprite
        switch(nPlayers) {
            case 0: 
                startX = 341;
                break;
            case 1:
                startX = 0;
                break;
            case 2:
                startX = 683;
                break;
        }//end switch
        position.x = startX;
        position.y = startY;

        for(int i = 0; i < hero.board().rows(); i++) {
            sf::Sprite sprite;
            for(int j = 0; j < hero.board().columns(); j++) {
                Coordinate c(i, j); //token coordinate
                sprite = spriteOf(hero.board()[c]);
                sprite.setPosition(position);
                position.x += sprite.getTextureRect().width;
                button.coord = c;
                button.sprite = sprite;
                otherSprites.push_back(button);
            }//end for j
            position.y += sprite.getTextureRect().height;
            position.x = startX;
        }//end for i

        nPlayers++;
        if(nPlayers >= 3) { 
            break; //done creating sprites for our players
        }
    }//end for Player *p

    //Step 1: draw the sprites to the window
    window.clear();
    for(auto sprite : heroSprites) {
        window.draw(sprite);
    }
    for(auto button : otherSprites) {
        window.draw(button.sprite);
    }
    window.display();

    //Step 2: handle window events that transpire
    bool done = false;
    do {
        sf::Event event;
        while(window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed: //user closes window
                    action = Close;
                    done = true;
                    break;
                case sf::Event::MouseButtonPressed: //user clicks something
                    for(auto button : otherSprites) {
                        //user clicked an enemy ship
                        if(util::clicked(button.sprite,sf::Mouse::Left,window)){
                            action = Continue;
                            done = true;
                            //find the player to shoot at, and shoot him
                            for(Player *p : others) {
                                if(!p) { continue; }
                                if(p->id() == button.playerId) { //player found
                                    hero.shoot(button.coord, *p); //shoot player!
                                }
                            }
                        }//end if(util::clicked())
                    }//end for
                    break;
                default: //some other event, ignore it yeh?
                    break;
            }//end switch
        }//end while
    }while(!done);

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
