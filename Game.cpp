/*
Brooks Kindle brooks.kindle@wsu.edu

Game.cpp    -       source file for Game class
*/

#include <algorithm>
#include <stdlib.h> //for rand() and srand()
#include <iostream>
#include <time.h> //for time()
#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "util.h"
using std::string;
using std::vector;
using std::cout;
using std::endl;

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
    Player *p = new ComputerPlayer();
    p->placeShips();
    players.push_back(p);

    p = new ComputerPlayer();
    p->placeShips();
    players.push_back(p);

    setStatus(Playing);
}//end showMainMenu


/* Displays the splash screen to the window */
void Game::showSplashScreen() {
    setStatus(ShowingMainMenu);
}//end showSplashScreen


/* Updates the logic of the game by one round. A round means
that each player gets to play one turn */
void Game::playRound() {
    displayGame();
    for(Player *p : players) {
            if(p && !p->dead()) {
                vector<Player *> others = players;
                others.erase(std::remove(others.begin(), others.end(), p));
                p->playTurn(others);
            }
    }
    util::pressEnterToContinue(); //wait for user confirmation before continuing
    if(finished()) { //only one player remains
        displayResults();
        setStatus(Exiting);
    }
}//end playRound


/* Prints the gameboards of each player to the screen */
void Game::displayGame() {
    for(Player *p : players) { //for each player
        if(!p) { //NULL player
            continue;
        }
        /* Display the game board for the player */
        cout << "Player #" << p->id() << endl;
        for(int i = 0; i < p->board().rows(); i++) {
            for(int j = 0; j < p->board().columns(); j++) {
                cout << p->board()[i][j];
            }//end for j
            cout << endl;
        }//end for i
        cout << "\n";
    }//end for Player *p
}//end displayGame


/* Displays the game results once the game is over. If the game is not over,
nothing will happen */
void Game::displayResults() {
    if(!finished()) {
        return; //game not over yet
    }

    cout << "\n\n\n\n\n";
    /* Step 1: Determine who the winner is */
    for(Player *p : players) {
        if(p && !p->dead()) {
            cout << "Player " << p->id() << " has vanquished all other" <<
                    " players.\n";
        }
    }//end for
}//end displayResults
