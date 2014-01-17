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
    TokenButton token;
    vector<TokenButton> tokens;
    sf::Sprite background;
    bool highlighted = false; //no token is highlighted yet
    sf::Sprite primaryHighlight;
    sf::IntRect primaryHighlightRect(0,0,34,30),
                  secondaryHighlightRect(34,0,34,30);
    vector<TokenButton> secondaryHighlights;
    primaryHighlight.setTexture(_highlight);
    background.setTexture(_background);
    primaryHighlight.setTextureRect(primaryHighlightRect);
    Board &board = player.getBoard();

    //Step 1: determine how much we need to scale our menu
    sf::Vector2f scale;
    scale.x = (float)Game::DEFAULT_WIDTH / _background.getSize().x;
    scale.y = (float)Game::DEFAULT_HEIGHT / _background.getSize().y;
    background.setScale(scale);

    //Step 2: create the tokens
    sf::Vector2i tokenStart;
    sf::FloatRect rect = spriteOf(Token::HitToken).getGlobalBounds();
    tokenStart.x = 341;
    tokenStart.y = 300 - rect.height * 5;
    sf::Vector2f position;
    position.x = tokenStart.x * scale.x;
    position.y = tokenStart.y * scale.y;
    for(int i = 0; i < player.board().rows(); i++) {
        for(int j = 0; j < player.board().columns(); j++) {
            Coordinate c(i, j); //token coordinate
            token.coord = c;
            token.playerId = player.id();
            sprite = spriteOf(player.board()[c]);
            sprite.setScale(scale); //scale the sprite
            sprite.setPosition(position);
            token.sprite = sprite;
            position.x += sprite.getGlobalBounds().width;
            tokens.push_back(token);
        }//end for j
        position.y += sprite.getGlobalBounds().height;
        position.x = tokenStart.x * scale.x;
    }//end for i

    //Step 3: Draw to the sprites to the window
    window.clear();
    window.draw(background);
    for(auto s : tokens) {
        window.draw(s.sprite);
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
                    for(auto s : tokens) {
                        if(util::clicked(s.sprite, sf::Mouse::Left, window)) {
                            if(highlighted) {  //a token already highlighted
                                highlighted = false;
                                //check to see if a secondary highlighted
                                //button is clicked
                                //if so, place the ship
                                for(auto t : secondaryHighlights) {
                                    sf::Sprite spr = t.sprite;
                                    if(util::clicked(spr, sf::Mouse::Left, window)) {
                                        //determine the direction to place ship
                                        Direction d = Direction::North;
                                        if(s.coord.col == t.coord.col) { //columns the same
                                            if(s.coord.row < t.coord.row) { //place ship south
                                                d = South;
                                            }
                                            else { //place ship north
                                                d = North;
                                            }
                                        }//end if
                                        else { //rows the same
                                            if(s.coord.col < t.coord.col) { //place ship east
                                                d = East;
                                            }
                                            else { //place ship west
                                                d = West;
                                            }
                                        }
                                        player.getBoard().place(Token::DestroyerToken,
                                            s.coord, d, 5);
                                    }//end if
                                }//end for(auto t...)
                                secondaryHighlights.clear();
                            }//end if
                            else { //no tokens highlighted
                                //highlight the clicked token
                                highlighted = true; 
                                primaryHighlight.setPosition(s.sprite.getPosition());
                                //figure out which sprites to highlight as secondary highlights
                                Coordinate c = s.coord; //location of the primary highlighted area
                                Coordinate newCoord = s.coord;
                                TokenButton token;
                                token.playerId = player.id();
                                token.sprite.setTexture(_highlight);
                                token.sprite.setTextureRect(secondaryHighlightRect);
                                if(board.contains(Token::SpaceToken, c, North, 5-1)) {
                                    newCoord = s.coord;
                                    newCoord.row -= 4;
                                    token.coord = newCoord;
                                    auto newPos = s.sprite.getPosition();
                                    newPos.y -= spriteOf(Token::SpaceToken).getGlobalBounds().height * 4 - spriteOf(Token::SpaceToken).getGlobalBounds().height / 2;
                                    token.sprite.setPosition(newPos);
                                    secondaryHighlights.push_back(token);
                                }
                                if(board.contains(Token::SpaceToken, c, South, 5-1)) {
                                    newCoord = s.coord;
                                    newCoord.row += 4;
                                    token.coord = newCoord;
                                    auto newPos = s.sprite.getPosition();
                                    newPos.y += spriteOf(Token::SpaceToken).getGlobalBounds().height * 4 + spriteOf(Token::SpaceToken).getGlobalBounds().height / 2;
                                    token.sprite.setPosition(newPos);
                                    secondaryHighlights.push_back(token);
                                }
                                if(board.contains(Token::SpaceToken, c, East, 5-1)) {
                                    newCoord = s.coord;
                                    newCoord.col += 4;
                                    token.coord = newCoord;
                                    auto newPos = s.sprite.getPosition();
                                    newPos.x += spriteOf(Token::SpaceToken).getGlobalBounds().width * 4 + spriteOf(Token::SpaceToken).getGlobalBounds().width / 2;
                                    token.sprite.setPosition(newPos);
                                    secondaryHighlights.push_back(token);
                                }
                                if(board.contains(Token::SpaceToken, c, West, 5-1)) {
                                    newCoord = s.coord;
                                    newCoord.col -= 4;
                                    token.coord = newCoord;
                                    auto newPos = s.sprite.getPosition();
                                    newPos.x -= spriteOf(Token::SpaceToken).getGlobalBounds().width * 4 - spriteOf(Token::SpaceToken).getGlobalBounds().width / 2;
                                    token.sprite.setPosition(newPos);
                                    secondaryHighlights.push_back(token);
                                }
                            }//end else
                        }
                    }//end for
                case sf::Event::GainedFocus:
                case sf::Event::Resized: //redraw items to the menu
                    window.clear();
                    window.draw(background);
                    for(auto s : tokens) {
                        window.draw(s.sprite);
                    }
                    if(highlighted) {
                        window.draw(primaryHighlight);
                        for(auto s : secondaryHighlights) {
                            window.draw(s.sprite);
                        }
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


/* Creates all the sprites needed for the placement menu. This will
delete any existing sprites the menu was using. */
void PlacementMenu::initialize(Player &player) {
    const Board &board = player.board();
    tokens.clear(); //remove any previously used tokens
    
    sf::Vector2f scale; //determine how much to scale everything
    scale.x = (float)Game::DEFAULT_WIDTH / _background.getSize().x;
    scale.y = (float)Game::DEFAULT_HEIGHT / _background.getSize().y;
    background.setScale(scale);

    sf::Vector2i spriteStart; //start position for the sprite
    spriteStart.x = 341;
    spriteStart.y = 300;
    sf::Vector2f position; //position of the current sprite
    position.x = spriteStart.x * scale.x;
    position.y = spriteStart.y * scale.y;

    //create a TokenButton for each token on the player's board
    for(int i = 0; i < board.rows(); i++) {
        TokenButton button;
        sf::Sprite sprite;
        for(int j = 0; j < board.columns(); j++) {
            Coordinate c(i, j); //token coordinate
            button.coord = c;
            button.playerId = player.id();
            sprite = spriteOf(player.board()[c]);
            sprite.setScale(scale); //scale the sprite
            sprite.setPosition(position);
            button.sprite = sprite;
            position.x += sprite.getGlobalBounds().width;
            tokens.push_back(button);
        }//end for j
        position.y += sprite.getGlobalBounds().height;
        position.x = spriteStart.x * scale.x;
    }//end for i
}//end generateSprites


/* Draws the placement menu to the screen. Does not clear or display the
window */
void PlacementMenu::draw(sf::RenderWindow &window) {
    for(auto tok : tokens) {
        window.draw(tok.sprite);
    }
}//end draw


/* Handles mouse clicks within the placement menu */
void PlacementMenu::handleClick(sf::RenderWindow &window) {
}//end handleClick