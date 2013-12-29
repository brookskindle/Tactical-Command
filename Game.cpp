/*
Brooks Kindle brooks.kindle@wsu.edu

Game.cpp    -       source file for Game class
*/

#include <algorithm>
#include <stdlib.h> //for rand() and srand()
#include <time.h> //for time()
#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
using std::string;
using std::vector;

//initialize Game attributes
Game::GameStatus Game::_status = Game::Uninitialized;
const string Game::GAME_NAME = "Tactical Command";
vector<Player *> Game::players;


/* starts the game if not already done so */
void Game::start() {
    if(getStatus() == Uninitialized) {
        srand(time(NULL)); //seed random values

        setStatus(ShowingSplashScreen);
        /* start the game */
        while(!isExiting()) {
            gameLoop();
        }

    }//end if(getStatus() == Uninitialized)
}//end start


/* returns the current status of the game */
Game::GameStatus Game::getStatus() {
    return _status;
}//end getStatus


/* sets the current game status */
void Game::setStatus(Game::GameStatus status) {
    Game::_status = status;
}//end setStatus


/* Returns whether or not the game is exiting */
bool Game::isExiting() {
       return _status == Exiting;
}//end isExiting


/* Returns whether or not the game is finished playing. This
is the same thing as saying if the number of players left
alive is equal to one */
bool Game::finished() {
    int alive = players.size(); //number of alive players
    for(Player *p : players) {
        if(p && p->dead()) {
            alive--;
        }
    }//end for
    return alive <= 1;
}//end finished


/* Runs and updates the game at each tick of the game clock */
void Game::gameLoop() {
    /* determine what to do based on what state the game is in */
    switch(_status) {
        case ShowingSplashScreen:
            showSplashScreen();
            break;
        case ShowingMainMenu:
            showMainMenu();
            break;
        case Playing:
            playRound();
            break;
        case Exiting:
        default:
            break;
    }//end switch(_status)
}//end gameLoop


/* Displays the start menu to the screen */
void Game::showMainMenu() {
    players.push_back(new HumanPlayer());
    players.push_back(new ComputerPlayer());
    setStatus(Playing);
}//end showMainMenu


/* Displays the splash screen to the window */
void Game::showSplashScreen() {
    setStatus(ShowingMainMenu);
}//end showSplashScreen


/* Updates the logic of the game by one round. A round means
that each player gets to play one turn */
void Game::playRound() {
    for(Player *p : players) {
            vector<Player *> others = players;
            if(p && !p->dead()) {
                others.erase(std::remove(others.begin(), others.end(), p));
                p->playTurn(others);
            }
    }
    if(finished()) { //only one player remains
        setStatus(Exiting);
    }
}//end playRound
