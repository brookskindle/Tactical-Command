/*
Brooks Kindle
brooks.kindle@wsu.edu

HumanPlayer.h   -   header file for HumanPlayer class
*/

#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"
#include "GameScreen.h"

/* A player that is human controlled */
class HumanPlayer : public Player {
    public:
        HumanPlayer();
        virtual ~HumanPlayer() override;
        virtual void placeShips() override;
        virtual void playTurn(const std::vector<Player *> &) const override;
    private:
        GameScreen _gameScreen;
};//end HumanPlayer

#endif
