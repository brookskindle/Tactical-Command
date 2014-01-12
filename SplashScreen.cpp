/*
Brooks Kindle
brooks.kindle@wsu.edu

SplashScreen.cpp    -       source file for SplashScreen class
*/

#include "SplashScreen.h"
#include "Game.h"
using std::string;

/* SplashScreen variable initialization */
const sf::Time SplashScreen::duration = sf::seconds(3.0);

/* Displays splash screen to the window and returns an exit status when done.
    Return value:       Reason:
    -------------------------------
    Failure         Unable to load splash screen
    Close           User closes window
    Continue        Splash screen finished displaying
*/
SplashScreen::ExitStatus SplashScreen::show(sf::RenderWindow &window) {
    string filename = "./SplashScreen.png";
    sf::Texture texture;
    ExitStatus status = Failure;

    if(texture.loadFromFile(filename)) { 
        status = Continue; //image loaded
        sf::Sprite sprite;
        sprite.setTexture(texture);

        /* determine how much to scale the image */
        sf::Vector2f scale(0.0, 0.0);
        scale.x = (float)Game::DEFAULT_WIDTH / texture.getSize().x;
        scale.y = (float)Game::DEFAULT_HEIGHT / texture.getSize().y;
        sprite.setScale(scale); //scale image

        /* clear screen and draw splash screen image to the window */
        window.clear();
        window.draw(sprite);
        window.display();

        sf::Clock clock;
        while(clock.getElapsedTime() < duration) {
        
            //handle events that occurred while showing the splash screen
            sf::Event e;
            while(window.pollEvent(e)) {
                if(e.type == sf::Event::Closed) {
                    status = Close; //user closed window
                }
                if(e.type == sf::Event::Resized) {
                    window.clear();
                    window.draw(sprite);
                    window.display();
                }
            }//end while
            if(status == Close) { 
                //early terminate splash screen if user closed window
                break;
            }
        }//end while
    }//end if
    return status;
}//end show
