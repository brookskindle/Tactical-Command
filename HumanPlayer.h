/*
Brooks Kindle
brooks.kindle@wsu.edu

HumanPlayer.h   -   header file for HumanPlayer class
*/

#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

/* A player that is human controlled */
class HumanPlayer : public Player {
    public:
        virtual ~HumanPlayer();
        virtual void playTurn(std::vector<Player> &others) const override;
};//end HumanPlayer

#endif
