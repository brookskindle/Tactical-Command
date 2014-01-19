/*
Brooks Kindle
brooks.kindle@wsu.edu

PlacementMenu.h -   header file for PlacementMenu class
*/
#include <iostream>
using namespace std;

#include "PlacementMenu.h"
#include "util.h"
#include "Game.h"
using std::vector;

/* constructs the placement menu */
PlacementMenu::PlacementMenu() :_nShipsPlaced(0), _highlighted(false),
_currentShip(DestroyerToken) {
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

    initialize(player);
    action = Continue;
    window.clear();
    draw(window);
    window.display();

    bool sdone = false;
    do {
        sf::Event e;
        while(window.pollEvent(e)) {

            /* Determine what to do for each window event */
            switch(e.type) {
                case sf::Event::Closed:
                    cout << "window closed" << endl;
                    action = Close;
                    sdone = true;
                    break;
                case sf::Event::MouseButtonPressed:
                    cout << "mouse pressed" << endl;
                    if(handleClick(window, player)) {
                        initialize(player);
                    }
                case sf::Event::GainedFocus:
                case sf::Event::Resized:
                    cout << "drawing window" << endl;
                    window.clear();
                    draw(window);
                    window.display();
                    break;
                default:
                    break;
            }//end switch

        }//end while(window.pollEvent(e))
    }while(!done() && !sdone);

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


/* Returns true if the placement menu are done placing
all of the ships. Returns false otherwise */
bool PlacementMenu::done() const {
    return _nShipsPlaced == 5;
}//end done


/* Highlights all tokens with the given highlight type */
void PlacementMenu::highlightAll(HighlightType type) {
    for(auto itr = tokens.begin(); itr != tokens.end(); itr++) {
        HighlightButton &b = *itr;
        b.highlightType = type;
    }
}//end highlightAll


/* Creates all the sprites needed for the placement menu. This will
delete any existing sprites the menu was using. */
void PlacementMenu::initialize(Player &player) {
    if(!loaded()) {
        return;
    }

    const Board &board = player.board();
    tokens.clear(); //remove any previously used tokens
    highlights.clear();
    
    sf::Vector2f scale; //determine how much to scale everything
    scale.x = (float)Game::DEFAULT_WIDTH / _background.getSize().x;
    scale.y = (float)Game::DEFAULT_HEIGHT / _background.getSize().y;
    background.setTexture(_background);
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
            HighlightButton button1 = {button, HighlightType::None};
            tokens.push_back(button1);
        }//end for j
        position.y += sprite.getGlobalBounds().height;
        position.x = spriteStart.x * scale.x;
    }//end for i
}//end initialize


/* Draws the placement menu to the screen. Does not clear or display the
window */
void PlacementMenu::draw(sf::RenderWindow &window) {
    if(loaded()) {
        window.draw(background);
        for(auto btn : tokens) {
            window.draw(btn.button.sprite);
        }
        for(auto highlight : highlights) {
            window.draw(highlight);
        }
    }
}//end draw


/* Handles mouse clicks within the placement menu, and returns
true if the click placed a ship */
bool PlacementMenu::handleClick(sf::RenderWindow &window, Player &player) {
    bool clickPlacedToken = false;
    if(!loaded()) {
        return clickPlacedToken;
    }

    cout << "Number of tokens: " << tokens.size() << endl;
    //Determine which, if any, token has been clicked
    for(auto itr = tokens.begin(); itr != tokens.end(); itr++) {
        HighlightButton &button = *itr;
        if(util::clicked(button.button.sprite, sf::Mouse::Left, window)) {
            switch(button.highlightType) {
                case HighlightType::None:
                    cout << "non-highlighted button pressed" << endl;
                    if(_highlighted) { //change highlighted token
                        highlightAll(None);
                        highlights.clear();
                        button.highlightType = Primary;
                        this->highlight(_currentShip);
                    }
                    else { //highlight token
                        _highlighted = true;
                        highlightAll(None);
                        highlights.clear();
                        button.highlightType = Primary;
                        this->highlight(_currentShip);
                    }
                    break;
                case HighlightType::Primary: //unhighlight the token
                    cout << "primary button pressed" << endl;
                    _highlighted = false;
                    highlightAll(None);
                    highlights.clear();
                    button.highlightType = None;
                    break;
                case HighlightType::Secondary: //place the ship!
                    clickPlacedToken = true;
                    cout << "secondary button pressed" << endl;
                    //make the button primary so we can place the ship
                    button.highlightType = Primary;
                    placeShip(player);
                    highlightAll(None);
                    highlights.clear();
                    _highlighted = false;
                    switch(_currentShip) {
                        case DestroyerToken:
                            _currentShip = FrigateToken;
                            _nShipsPlaced++;
                            break;
                        case FrigateToken:
                            _currentShip = CrusaderToken;
                            _nShipsPlaced++;
                            break;
                        case CrusaderToken:
                            _currentShip = ValkyrieToken;
                            _nShipsPlaced++;
                            break;
                        case ValkyrieToken:
                            _currentShip = InterceptorToken;
                            _nShipsPlaced++;
                            break;
                        case InterceptorToken:
                            _nShipsPlaced++;
                        default:
                            break;
                    }//end switch
                    break;
            }//end switch
        }//end if
    }//end for
    return clickPlacedToken;
}//end handleClick


/* Clears and re-highlights all highlighted sprites */
void PlacementMenu::highlight(Token ship) {
    highlights.clear();
    sf::IntRect primaryHighlight,
                secondaryHighlight;
    primaryHighlight.top = 0;
    primaryHighlight.left = 0;
    primaryHighlight.width = 34;
    primaryHighlight.height = 30;

    secondaryHighlight.top = 0;
    secondaryHighlight.left = 34;
    secondaryHighlight.width = 34;
    secondaryHighlight.height = 30;

    int offset = 0;
    switch(ship) {
        case DestroyerToken:
            offset++;
        case FrigateToken:
            offset++;
        case CrusaderToken:
        case ValkyrieToken:
            offset++;
        case InterceptorToken:
            offset += 1;
        default:
            break;
    }//end switch

    //find primary highlighted token and then calculate secondary from there
    Coordinate coord(-15,-15); //coordinate of primary highlighted token
    for(auto hl : tokens) {
        if(hl.highlightType == Primary) {
            coord = hl.button.coord;
            sf::Sprite sprite;
            sprite.setTexture(_highlight);
            sprite.setTextureRect(primaryHighlight);
            sprite.setPosition(hl.button.sprite.getPosition());
            highlights.push_back(sprite);
            break;
        }
    }//end for

    Coordinate cNorth(coord),
               cSouth(coord),
               cEast(coord),
               cWest(coord);
    cNorth.row -= offset;
    cSouth.row += offset;
    cEast.col += offset;
    cWest.col -= offset;

    //find secondary highlighted tokens
    for(auto hl : tokens) {
        if(hl.button.coord == cNorth ||
           hl.button.coord == cSouth ||
           hl.button.coord == cEast  ||
           hl.button.coord == cWest) {
            sf::Sprite sprite;
            sprite.setTexture(_highlight);
            sprite.setTextureRect(secondaryHighlight);
            sprite.setPosition(hl.button.sprite.getPosition());
            highlights.push_back(sprite);
        }
    }//end for
}//end highlightSecondary


/* Places the current ship between the two locations
that are primary highlighted */
void PlacementMenu::placeShip(Player &player) {
    bool firstFound = false,
         secondFound = false;
    Coordinate first,
               second;
    for(auto token : tokens) {
        if(token.highlightType == Primary) {
            if(!firstFound) {
                firstFound = true;
                first = token.button.coord;
            }
            else if(!secondFound) {
                secondFound = true;
                second = token.button.coord;
            }
        }
        if(secondFound) {
            break;
        }

        //now that we've found both primary coordinates,
        //let's place our ships between them
        Direction d(North);
        if(first.col < second.col) { //go east
            d = East;
        }
        else if(first.row < second.row) { //go south
            d = South;
        }
        
        int shipLen = 0;
        switch(_currentShip) {
            case DestroyerToken:
                shipLen++;
            case FrigateToken:
                shipLen++;
            case CrusaderToken:
            case ValkyrieToken:
                shipLen++;
            case InterceptorToken:
                shipLen += 2;
            default:
                break;
        }

        //place the ship
        player.getBoard().place(_currentShip, first, d, shipLen);
    }//end for
}//end placeShip
