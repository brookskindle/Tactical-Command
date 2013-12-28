/*
Brooks Kindle
brooks.kindle@wsu.edu

Game.h      -       header file for Game class
*/

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

/* the game itself */
class Game {
    public:
        static const std::string GAME_NAME;
        enum GameStatus {
            Uninitialized, Playing, Exiting, ShowingMainMenu,
            ShowingHelpMenu, ShowingSplashScreen
        };

        static void start();
        static GameStatus getStatus();
        static void setStatus(GameStatus stat);
        static sf::RenderWindow &getWindow();
        //static GameObjectManager &getGameObjectManager();
        //static World &getWorld();

    private:
        static bool isExiting();
        static void gameLoop();
        static void showMainMenu();
        static void showHelpMenu();
        static void showSplashScreen();

        //attributes
        static GameStatus status;
        static sf::Clock clock;
        //static GameObjectManager _gameObjectManager;
        //static World _world;
};//end Game

#endif