/*
Brooks Kindle
brooks.kindle@wsu.edu

MainMenu.h          -       header file for MainMenu class
*/

#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>

/* Main game menu */
class MainMenu {
    public:
        enum MenuAction {
            Failure, Play, Exit
        };

        MainMenu();
        ~MainMenu();
        bool loaded() const;
        MenuAction show(sf::RenderWindow &window);
    private:
        bool _loaded;
        sf::Texture _background; //main menu background texture
        sf::Texture _playButton; //play button texture
        sf::Texture _exitButton; //exit button texture
};//end MainMenu

#endif
