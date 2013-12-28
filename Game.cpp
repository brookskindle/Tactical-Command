/*
Brooks Kindle brooks.kindle@wsu.edu

Game.cpp    -       source file for Game class
*/

#include <iostream>
#include <string>
#include <assert.h>
#include "Game.h"
using std::vector;
using std::string;

//initialize Game attributes
Game::GameStatus Game::status = Game::Uninitialized;
sf::Clock Game::clock;
//GameObjectManager Game::_gameObjectManager;
const string Game::GAME_NAME = "Devil Dogs";
//World Game::_world;


/* starts the game if not already done so */
void Game::start() {
    if(getStatus() == Uninitialized) {
        setStatus(ShowingSplashScreen);
        clock.restart(); //restart clock at 0.0
        /* start the game */
        while(!isExiting()) {
            gameLoop();
        }

    }//end if(getStatus() == Uninitialized)
}//end start


/* returns the current status of the game */
Game::GameStatus Game::getStatus() {
    return status;
}//end getStatus


/* sets the current game status */
void Game::setStatus(Game::GameStatus stat) {
    Game::status = stat;
}//end setStatus

//
///* Returns the game object manager */
//GameObjectManager &Game::getGameObjectManager() {
//    return _gameObjectManager;
//}//end getGameObjectManager


///* Returns the game world */
//World &Game::getWorld() {
//    return _world;
//}//end getWorld


/* Returns whether or not the game is exiting */
bool Game::isExiting() {
       return status == Exiting;
}//end isExiting


/* Runs and updates the game at each tick of the game clock */
void Game::gameLoop() {
    float elapsedTime = clock.restart().asSeconds();

    /* determine what to do based on what state the game is in */
    switch(status) {
        case ShowingSplashScreen:
            showSplashScreen();
            break;
        case ShowingHelpMenu:
            showHelpMenu();
            break;
        case ShowingMainMenu:
            showMainMenu();
            break;
        case Playing:
            ////update and draw objects, clear and redraw window
            //_world.updateAll(elapsedTime);
            //_gameObjectManager.updateAll(elapsedTime);
            break;
        case Exiting:
        default:
            break;
    }//end switch(status)
}//end gameLoop


/* Displays the start menu to the screen */
void Game::showMainMenu() {
    //MainMenu menu;
    //switch(menu.show()) {
    //    case MainMenu::Campaign:
    //        if(_world.load("../worlds/alpha.world")) {
    //            setStatus(Playing); //world loaded, let's play it!
    //        }
    //        timeout(1);
    //        break;
    //    case MainMenu::Failure:
    //    case MainMenu::Multiplayer:
    //    case MainMenu::GameOverview:
    //    case MainMenu::Settings:
    //    case MainMenu::Credits:
    //        cout << "Not implemented yet" << endl;
    //    case MainMenu::Exit:
    //        setStatus(Exiting);
    //        break;
    //}//end switch
    clock.restart(); //restart the clock
    setStatus(Playing);
}//end showMainMenu


/* Displays the help menu to the screen */
void Game::showHelpMenu() {
    setStatus(Playing);
}//end showHelpMenu


/* Displays the splash screen to the window */
void Game::showSplashScreen() {
    //switch(SplashScreen::show()) {
    //    case SplashScreen::CONTINUE:
    //        setStatus(ShowingMainMenu);
    //        break;
    //    case SplashScreen::FAILURE:
    //    case SplashScreen::CLOSE:
    //        setStatus(Exiting);
    //        break;
    //}//end switch
    setStatus(ShowingMainMenu);
}//end showSplashScreen