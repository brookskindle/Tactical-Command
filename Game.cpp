/*
Brooks Kindle brooks.kindle@wsu.edu

Game.cpp    -       source file for Game class
*/

#include "Game.h"
using std::string;

//initialize Game attributes
Game::GameStatus Game::_status = Game::Uninitialized;
const string Game::GAME_NAME = "Devil Dogs";


/* starts the game if not already done so */
void Game::start() {
    if(getStatus() == Uninitialized) {
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
void Game::setStatus(Game::GameStatus stat) {
    Game::_status = stat;
}//end setStatus


/* Returns whether or not the game is exiting */
bool Game::isExiting() {
       return _status == Exiting;
}//end isExiting


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
    setStatus(Playing);
}//end showMainMenu


/* Displays the splash screen to the window */
void Game::showSplashScreen() {
    setStatus(ShowingMainMenu);
}//end showSplashScreen


/* Updates the logic of the game by one round. A round means
that each player gets to play one turn */
void Game::playRound() {
    setStatus(Exiting);
}//end playRound