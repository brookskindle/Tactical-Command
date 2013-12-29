/*
Brooks Kindle
brooks.kindle@wsu.edu

Game.h      -       header file for Game class
*/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "Player.h"

/* the game itself */
class Game {
    public:
        static const std::string GAME_NAME;
        enum GameStatus {
            Uninitialized, Playing, Exiting, ShowingMainMenu,
            ShowingSplashScreen
        };
        static void start();
        static GameStatus getStatus();
        static void setStatus(GameStatus status);
    private:
        static bool isExiting();
        static bool finished();
        static void gameLoop();
        static void showMainMenu();
        static void showSplashScreen();
        static void playRound();
        static void displayGame();

        //attributes
        static GameStatus _status;
        static std::vector<Player *> players;
};//end Game

#endif
