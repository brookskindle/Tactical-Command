/*
Brooks Kindle
brooks.kindle@wsu.edu

HumanPlayer.cpp -   contains HumanPlayer (class) source code
*/

#include <iostream>
#include "HumanPlayer.h"
#include "Game.h"
#include "util.h"
using std::vector;

/* Constructs the human player */
HumanPlayer::HumanPlayer() {
}//end constructor


/* Destructs the player */
HumanPlayer::~HumanPlayer() {
}//end destructor


/* Places ship tokens on the player's board */
void HumanPlayer::placeShips() {
    util::placeAllShipsRandomly(this->getBoard());
}//end placeShips


/* Plays one turn of the player (which probably involves
firing shots at one of the other players) */
void HumanPlayer::playTurn(const std::vector<Player *> &others) const {
    switch(_gameScreen.playTurn(Game::getWindow(), *this, others)) {
        case GameScreen::Failure:
        case GameScreen::Close:
            Game::setStatus(Game::Exiting);
        case GameScreen::Continue:
            break;
    }//end switch
}//end playTurn
