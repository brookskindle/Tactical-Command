/*
Brooks Kindle
brooks.kindle@wsu.edu

util.cpp    -   source file for util namespace
*/

#include <iostream>
#include <limits>
#include <algorithm>
#include "util.h"
using std::cout;
using std::cin;
using std::endl;

/* waits for the user to press enter before returning */
void util::pressEnterToContinue() {
    cout << "Press <enter> to continue.\n" << std::flush;
    cin.sync();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}//end pressEnterToContinue



/* Returns true if the given sprite is being
clicked by the specified mouse button */
bool util::clicked(const sf::Sprite &sprite, sf::Mouse::Button button,
                   const sf::RenderWindow &relativeTo) {
    bool click = false;
    if(sf::Mouse::isButtonPressed(button)) { //correct button is pressed
        //get the mouse position in "world coordinates"
        sf::Vector2f mouse = relativeTo.mapPixelToCoords(sf::Mouse::getPosition(relativeTo));

        //get global (with scales, transforms, etc) bounding box of sprite
        sf::FloatRect bounds = sprite.getGlobalBounds();

        if(bounds.contains(mouse)) { //sprite has indeed been clicked
            click = true;
        }
    }//end if
    return click;
}//end clicked


/* Places the ship token randomly on the board and returns true if successful,
false otherwise */
bool util::placeRandom(Board &board, Token ship) {
    int len = 2;
    switch(ship) {
    case Token::DestroyerToken:
        len++;
    case Token::FrigateToken:
        len++;
    case Token::CrusaderToken:
    case Token::ValkyrieToken:
        len++;
    case Token::InterceptorToken:
    default:
        break;
    }//end switch

    //Loop until we find a valid coordinate and direction to place the ship
    bool placed = false;
    Coordinate c;
    auto directions = allDirections();
    std::random_shuffle(directions.begin(), directions.end());
    do {
        c.row = rand() % board.rows();
        c.col = rand() % board.columns();
        for(Direction d : directions) { 
            if(board.place(ship, c, d, len)) {
                placed = true; 
                break;
            }
        }//end for
    }while(!placed);

    return placed;
}//end place


/* Places all of the ships randomly on the given board */
bool util::placeAllShipsRandomly(Board &board) {
    //place DestroyerToken (5 spots)
    util::placeRandom(board, Token::DestroyerToken);
    //place FrigateToken (4 spots)
    util::placeRandom(board, Token::FrigateToken);
    //place CrusaderToken (3 spots)
    util::placeRandom(board, Token::CrusaderToken);
    //place vaklyrie (3 spots)
    util::placeRandom(board, Token::ValkyrieToken);
    //place InterceptorToken (2 spots)
    util::placeRandom(board, Token::InterceptorToken);

    return true;
}//end placeAllShipsRandomly