/*
Brooks Kindle
brooks.kindle@wsu.edu

Player.h    -   header file for Player class
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Board.h"
#include "Coordinate.h"


/* Abstract class for game players (could be user 
controlled or computer controlled) */
class Player {
    public:
        struct Shot {
            int targId;
            Coordinate coord;
            Shot(int t, Coordinate c):targId(t), coord(c) {}
            Shot(Coordinate c,int t):targId(t), coord(c) {}
        };
        Player();
        Player(const Player &);
        Player &operator=(const Player &);
        virtual ~Player() = 0;
        int id() const;
        const Board &board() const;
        virtual void playTurn(std::vector<Player> &others) const = 0;
        bool dead() const;
    protected:
        bool shoot(Coordinate loc, Player &targ) const;
        Board &board();
    private:
        const int _id;
        Board _board;
};//end Player

#endif
