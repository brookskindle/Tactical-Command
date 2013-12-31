/*
Brooks Kindle
brooks.kindle@wsu.edu

SplashScreen.h      -       header file for SplashScreen class
*/

#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <SFML/Graphics.hpp>

/* Screen that is displayed when the game first starts up */
class SplashScreen {
    public:
        enum ExitStatus {
            Failure, Close, Continue
        };
        static ExitStatus show(sf::RenderWindow &window);
    private:
        static const sf::Time duration; //splash screen duration
};//end SplashScreen

#endif
