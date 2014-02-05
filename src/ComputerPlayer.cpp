/*
Brooks Kindle
brooks.kindle@wsu.edu

ComputerPlayer.cpp    -   source file for ComputerPlayer class
*/

#include <stdlib.h>
#include "ComputerPlayer.h"
#include "util.h"
using std::vector;

/* Destructs the player */
ComputerPlayer::~ComputerPlayer() {
}//end destructor


/* Places the ship tokens on the board */
void ComputerPlayer::placeShips() {
    util::placeAllShipsRandomly(getBoard());
}//end placeShips


/* Plays a turn for the player */
void ComputerPlayer::playTurn(const vector<Player *> &others) const {
    /* determine randomly which player to shoot at */
    int i = 0;
    do {
    i = rand() % others.size();
    }while(!others[i] || others[i]->dead());

    /* randomly pick coordinates and shoot at it */
    Coordinate c;
    do { //pick until we find a spot that hasn't been shot at before
    c.row = rand() % others[i]->board().rows();
    c.col = rand() % others[i]->board().columns();
    }while(others[i]->board()[c.row][c.col] == HitToken ||
           others[i]->board()[c.row][c.col] == MissToken);

    
    /* now shoot at him, robot! */
    shoot(c, *others[i]);
}//end playTurn
