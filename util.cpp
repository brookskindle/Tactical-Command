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
using std::vector;
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


/* Returns true if the given text is being
clicked by the specified mouse button */
bool util::clicked(const sf::Text &text, sf::Mouse::Button button,
                   const sf::RenderWindow &relativeTo) {
    bool click = false;
    if(sf::Mouse::isButtonPressed(button)) { //correct button is pressed
        //get the mouse position in "world coordinates"
        sf::Vector2f mouse = relativeTo.mapPixelToCoords(sf::Mouse::getPosition(relativeTo));

        //get global (with scales, transforms, etc) bounding box of sprite
        sf::FloatRect bounds = text.getGlobalBounds();

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


/* Returns a vector of coordinates starting from the given coordinate
and going in a direction for a certain length. For example, if the coordinate
was (0,0), the direction South, and the length 3, then the vector
would contain the coordinates (0,0), (1,0), (2,0) */
vector<Coordinate> util::generateCoordinates(Coordinate c, Direction d,
                                              unsigned int len) {
    vector<Coordinate> coords;

    /* Step 1: Determine the row and column offset 
    for each successive coordinate we generate */
    int rowOffset = 0, //row offset for the direction we're going
        colOffset = 0; //column offset

    if(d & North) { //direction is north
        rowOffset -= 1;
    }
    if(d & South) { //direction is south
        rowOffset += 1;
    }
    if(d & East) { //direction is east
        colOffset += 1;
    }
    if(d & West) { //direction is west
        colOffset -= 1;
    }

    /* Step 2: Generate each coordinate and push it to our result vector */
    for(int i = 0; i < len; i++) {
        coords.push_back(c);
        c.row += rowOffset;
        c.col += colOffset;
    }//end for

    return coords;
}//end generateCoordinates


/* Returns a path between two coordinate on the same line */
vector<Coordinate> util::pathBetween(Coordinate c1, Coordinate c2) {
    vector<Coordinate> coords;
    
    if(c1.row == c2.row || //coordinates on same line
       c1.col == c2.col) {
        int dist = 0;
        Direction d(North);
        if(c1.col < c2.col) { //go east
            dist = c2.col - c1.col;
            d = East;
        }
        else if(c1.col > c2.col) { //go west
            dist = c1.col - c2.col;
            d = West;
        }
        else if(c1.row < c2.row) { //go south
            dist = c2.row - c1.row;
            d = South;
        }
        else { //do north
            dist = c1.row - c2.row;
            d = North;
        }
        
        coords = util::generateCoordinates(c1, d, ++dist);
    }//end if

    return coords;
}//end pathBetween
