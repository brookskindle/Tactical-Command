/*
Brooks Kindle
brooks.kindle@wsu.edu

ScoreScreen.cpp   -   source file for ScoreScreen class
*/

#include "ScoreScreen.h"
#include "Game.h"
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
        return action;
    }

    /* Step 1: find out who the winner is */
    const Player *winner = NULL;
    for(auto *p : players) {
        if(!p || p->dead()) {
            winner = p;
            break;
        }
    }

    if(!winner) { //nobody won, so why are we even showing this screen?
        return action;
    }

    //Step 2: display the winner to the screen
    sf::Text text;
    sf::Sprite background;
    sf::Vector2f scale;
    scale.x = (float)Game::DEFAULT_WIDTH / _background.getSize().x;
    scale.y = (float)Game::DEFAULT_HEIGHT / _background.getSize().y;

    background.setTexture(_background);
    background.setScale(scale); //scale background
    text.setFont(_font);
    text.setScale(scale); //scale font
    text.setString("Player #"+std::to_string(winner->id())+" is the winner");

    //place text in middle of screen
    float tWidth = text.getGlobalBounds().width, //text width
          tHeight= text.getGlobalBounds().height;//text height
    auto  bbounds = background.getGlobalBounds(); //background bounds
    text.setPosition((bbounds.width - tWidth) / 2.0,
                     (bbounds.height - tHeight) / 2.0);

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
                case sf::Event::GainedFocus:
                case sf::Event::Resized:
                    window.clear();
                    window.draw(background);
                    window.draw(text);
                    window.display();
                default:
                    break;
            }//end switch
        }//end while
    }while(!done);

    return action;
}//end show
