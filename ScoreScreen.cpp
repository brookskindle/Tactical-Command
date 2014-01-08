/*
Brooks Kindle
brooks.kindle@wsu.edu

ScoreScreen.cpp   -   source file for ScoreScreen class
*/

#include <iostream>
using namespace std;
#include "ScoreScreen.h"
using std::vector;

/* Constructs the score screen */
ScoreScreen::ScoreScreen() {
    _loaded = (_background.loadFromFile("./ScoreScreen.png") &&
               _font.loadFromFile("./Starjedi.ttf")) ? true : false;
}//end constructor


/* Returns whether or not the score screen has successfully
loaded itself */
bool ScoreScreen::loaded() const {
    return _loaded;
}//end loaded


/* Displays the score screen the the window */
ScoreScreen::ExitStatus ScoreScreen::show(sf::RenderWindow &window,
                                        const vector<Player *> &players) const {
    //Step 0: make sure everything is loaded
    ExitStatus action = Failure;
    if(!loaded()) {
        cout << "Score Screen not loaded" << endl;
        return action;
    }
    cout << "Score Screen loaded" << endl;

    /* Step 1: find out who the winner is */
    const Player *winner = NULL;
    for(auto *p : players) {
        if(!p || p->dead()) {
            winner = p;
            break;
        }
    }

    if(!winner) { //nobody won, so why are we even showing this screen?
        cout << "There is no winner!" << endl;
        return action;
    }

    //Step 2: display the winner to the screen
    sf::Text text;
    sf::Sprite background;
    sf::Vector2f scale;
    scale.x = (float)window.getSize().x / _background.getSize().x;
    scale.y = (float)window.getSize().y / _background.getSize().y;

    background.setTexture(_background);
    background.setScale(scale); //scale background
    text.setFont(_font);
    text.setScale(scale); //scale font
    text.setString("Player #"+std::to_string(winner->id())+" is the winner");

    //place text in middle of screen
    text.setPosition(background.getGlobalBounds().width / 2.0,
                     background.getGlobalBounds().height / 2.0);

    cout << "Drawing score screen to window.. NOW" << endl;
    window.clear();
    window.draw(background);
    window.draw(text);
    window.display();

    //Step 3: handle window events
    bool done = false;
    sf::Event e;
    do {
        while(window.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::Closed:
                    action = Close;
                    done = true;
                    break;
                case sf::Event::MouseButtonPressed:
                    action = Continue;
                    done = true;
                    break;
                default:
                    break;
            }//end switch
        }//end while
    }while(!done);

    return action;
}//end show
