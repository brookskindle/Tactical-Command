/*
Brooks Kindle
brooks.kindle@wsu.edu

Player.cpp  -   source file for Player class
*/

#include <vector>
#include "Player.h"
using std::vector;

//file scoped variables///////////
int ID = 0;                     //
const unsigned int NROWS = 10;  //
const unsigned int NCOLS = 10;  //
//////////////////////////////////


/* Constructs the player with a playing board of size NROWS x NCOLS */
Player::Player() :_id(ID++), _board(NROWS, NCOLS) {
}//end constructor


/* Destructs the player */
Player::~Player() {
}//end destructor


/* Returns the id of the player */
int Player::id() const {
    return _id;
}//end id


/* Returns the player's game board */
const Board &Player::board() const {
    return _board;
}//end board


/* Return true if all of the player's ships have been blown up,
else return false */
bool Player::dead() const {
    //TODO: complete this (Player::dead)
}//end dead


/* Fires a shot at another player. Return true if a hit, else return false */
bool Player::shoot(Coordinate loc, Player &targ) const {
    //TODO: finish this function (Player::shoot)
}//end shoot