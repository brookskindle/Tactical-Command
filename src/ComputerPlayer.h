/*
Brooks Kindle
brooks.kindle@wsu.edu

ComputerPlayer.h    -   header file for ComputerPlayer class
*/

#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "Player.h"

/* A player that is controlled by the computer */
class ComputerPlayer : public Player {
    public:
        virtual ~ComputerPlayer() override;
        virtual void placeShips() override;
        virtual void playTurn(const std::vector<Player *> &) const override;
};//end ComputerPlayer

#endif
