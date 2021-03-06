/*
Brooks Kindle
brooks.kindle@wsu.edu

Game.h      -       header file for Game class
*/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Player.h"

/* the game itself */
class Game {
    public:
        static const std::string GAME_NAME;
        static const int DEFAULT_WIDTH;
        static const int DEFAULT_HEIGHT;
        enum GameStatus {
            Uninitialized, Playing, Exiting, ShowingMainMenu,
            ShowingSplashScreen, ShowingScoreScreen
        };
        static void start();
        static sf::RenderWindow &getWindow();
        static GameStatus getStatus();
        static void setStatus(GameStatus status);
    private:
        static bool isExiting();
        static bool finished();
        static void gameLoop();
        static void showMainMenu();
        static void showSplashScreen();
        static void showScoreScreen();
        static void playRound();
        static void displayGame();
        static void displayResults();

        //attributes
        static sf::RenderWindow _window;
        static sf::Image _icon;
        static GameStatus _status;
        static std::vector<Player *> players;
};//end Game

#endif
