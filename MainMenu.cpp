/*
Brooks Kindle
brooks.kindle@wsu.edu

MainMenu.cpp        -       source file for MainMenu class
*/

#include <string>
#include "MainMenu.h"
using std::string;

#include <iostream>
using namespace std;

/* Constructs the MainMenu */
MainMenu::MainMenu() :_loaded(false) {
    if(_background.loadFromFile("SplashScreen.png") &&
       _playButton.loadFromFile("./PlayButton.png") &&
       _exitButton.loadFromFile("./ExitButton.png")) {
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
    sf::Event event;

    while(!done) {
        while(window.pollEvent(event)) {
            //clear and redraw the window
            window.clear();
            window.draw(background);
            window.draw(playButton);
            window.draw(exitButton);
            window.display();

            /* Determine what to do given a window event */
            switch(event.type) {
                case sf::Event::Closed: //window closed
                    action = Exit;
                    done = true;
                    break;
                case sf::Event::MouseButtonPressed: //button clicked
                    //left button clicked
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        //get the mouse position relative to the window
                        auto pos = sf::Mouse::getPosition(window); 
                    }
                    break;
                default: //some other event, who cares about that?
                    break;
            }//end switch
        }//end while(window.pollEvent(event))
    }//end while(!done)

    cout << "Done showing main menu!" << endl;
    return action;
}//end show
