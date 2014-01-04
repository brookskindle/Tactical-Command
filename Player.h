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
        enum ShotType {
            Invalid = -1, Miss, Hit, SinkingHit
        };
        Player();
        Player(const Player &);
        Player &operator=(const Player &);
        virtual ~Player() = 0;
        int id() const;
        const Board &board() const;
        virtual void placeShips() = 0;
        virtual void playTurn(const std::vector<Player *> &) const = 0;
        bool dead() const;
        ShotType shoot(Coordinate loc, Player &targ) const;
    protected:
        Board &getBoard();
    private:
        const int _id;
        Board _board;
};//end Player

#endif
