/*
Brooks Kindle
brooks.kindle@wsu.edu

MainMenu.cpp        -       source file for MainMenu class
*/

#include <string>
#include "MainMenu.h"
#include "Game.h"
#include "util.h"
using std::string;

/* Constructs the MainMenu */
MainMenu::MainMenu() :_loaded(false) {
    if(_background.loadFromFile("../resource/MainMenu.png") &&
       _playButton.loadFromFile("../resource/PlayButton.png") &&
       _exitButton.loadFromFile("../resource/ExitButton.png")) {
        _loaded = true;
    }
}//end constructor


/* Destructs the main menu */
MainMenu::~MainMenu() {
}//end destructor


/* Returns whether or not the main menu is loaded */
bool MainMenu::loaded() const {
    return _loaded;
}//end loaded


/* Displays the main menu to the window and returns a menu action when done
    Return value:       Reason:
    -------------------------------
    Failure         Unable to load menu
    Play            User wishes to play
    Exit            User wishes to exit
*/
MainMenu::MenuAction MainMenu::show(sf::RenderWindow &window) {
    MenuAction action = Failure;
    bool done = false;
    sf::Sprite background,
               playButton,
               exitButton;

    if(!loaded()) { //main menu not loaded
        return action;
    }

    background.setTexture(_background);
    playButton.setTexture(_playButton);
    exitButton.setTexture(_exitButton);

    //determine how much to scale our sprites
    sf::Vector2f scale(0.0, 0.0);
    scale.x = (float)Game::DEFAULT_WIDTH / _background.getSize().x;
    scale.y = (float)Game::DEFAULT_HEIGHT / _background.getSize().y;

    //now scale them!
    background.setScale(scale);
    playButton.setScale(scale);
    exitButton.setScale(scale);

    //move buttons to appropriate locations
    sf::Vector2f position;
    position.x = background.getGlobalBounds().width - exitButton.getGlobalBounds().width;
    position.y = background.getGlobalBounds().height - exitButton.getGlobalBounds().height;
    exitButton.setPosition(position); //move exit button

    position.x = exitButton.getPosition().x;
    position.y = exitButton.getPosition().y - playButton.getGlobalBounds().height;
    playButton.setPosition(position); //move play button
//    exitButton.setPosition(background.getGlobalBounds().width -
//                            exitButton.getGlobalBounds().width,
//                           window.getSize().y -
//                            exitButton.getGlobalBounds().height);
//    playButton.setPosition(exitButton.getPosition().x,
//                           exitButton.getPosition().y -
//                            playButton.getGlobalBounds().height);
//
//    /* loop the main menu until the user chooses to do something */
    //draw the menu
    window.clear();
    window.draw(background);
    window.draw(playButton);
    window.draw(exitButton);
    window.display();

    while(!done) {
        sf::Event event;
        while(window.pollEvent(event)) {
            /* Determine what to do given a window event */
            switch(event.type) {
                case sf::Event::Closed: //window closed
                    action = Exit;
                    done = true;
                    break;
                case sf::Event::MouseButtonPressed: //button clicked
                    //play button pressed
                    if(util::clicked(playButton, sf::Mouse::Left, window)) {
                        action = Play;
                        done = true;
                    }
                    //exit button pressed
                    else if(util::clicked(exitButton, sf::Mouse::Left, window)) {
                        action = Exit;
                        done = true;
                    }
                    break;
                case sf::Event::GainedFocus:
                case sf::Event::Resized:
                    //clear and redraw the window
                    window.clear();
                    window.draw(background);
                    window.draw(playButton);
                    window.draw(exitButton);
                    window.display();
                default: //some other event, who cares about that?
                    break;
            }//end switch
        }//end while(window.pollEvent(event))
    }//end while(!done)

    return action;
}//end show
