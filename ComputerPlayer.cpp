/*
Brooks Kindle
brooks.kindle@wsu.edu

ComputerPlayer.cpp    -   source file for ComputerPlayer class
*/

#include <stdlib.h>
#include "ComputerPlayer.h"
using std::vector;

/* Destructs the player */
ComputerPlayer::~ComputerPlayer() {
}//end destructor


/* Plays a turn for the player */
void ComputerPlayer::playTurn(const vector<Player *> &others) const {
    /* determine randomly which player to shoot at */
    int i = rand() % others.size();

    /* randomly pick coordinates and shoot at it */
    Coordinate c;
    do { //pick until we find a spot that hasn't been shot at before
    c.row = rand() % others[i]->board().rows();
    c.col = rand() % others[i]->board().columns();
    }while(others[i]->board()[c.row][c.col] == hit ||
           others[i]->board()[c.row][c.col] == miss);

    
    /* now shoot at him, robot! */
    shoot(c, *others[i]);
}//end playTurn
