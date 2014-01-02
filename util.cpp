/*
Brooks Kindle
brooks.kindle@wsu.edu

util.cpp    -   source file for util namespace
*/

#include <iostream>
#include <limits>
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
