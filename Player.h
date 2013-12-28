/*
Brooks Kindle
brooks.kindle@wsu.edu

Player.h    -   header file for Player class
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include "Coordinate.h"

namespace std {
    template <class Player>
    class vector; //forward declare vector
};

/* Abstract class for game players (could be user 
controlled or computer controlled) */
class Player {
    public:
        Player();
        virtual ~Player() = 0;
        int id() const;
        const Board &board() const;
        virtual void playTurn(std::vector<Player> &others) const = 0;
        bool dead() const;
    protected:
        bool shoot(Coordinate loc, Player &targ) const;
    private:
        const int _id;
        Board _board;
};//end Player

#endif