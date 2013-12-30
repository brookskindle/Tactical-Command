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


/* Places the ship tokens on the board */
void ComputerPlayer::placeShips() {
    //place DestroyerToken (5 spots)
    int row = 0, col = 0;
    getBoard()[row++][col] = Token::DestroyerToken;
    getBoard()[row++][col] = Token::DestroyerToken;
    getBoard()[row++][col] = Token::DestroyerToken;
    getBoard()[row++][col] = Token::DestroyerToken;
    getBoard()[row++][col++] = Token::DestroyerToken;

    //place FrigateToken (4 spots)
    row = 0;
    getBoard()[row++][col] = Token::FrigateToken;
    getBoard()[row++][col] = Token::FrigateToken;
    getBoard()[row++][col] = Token::FrigateToken;
    getBoard()[row++][col++] = Token::FrigateToken;

    //place CrusaderToken (3 spots)
    row = 0;
    getBoard()[row++][col] = Token::CrusaderToken;
    getBoard()[row++][col] = Token::CrusaderToken;
    getBoard()[row++][col++] = Token::CrusaderToken;

    //place vaklyrie (3 spots)
    row = 0;
    getBoard()[row++][col] = Token::ValkyrieToken;
    getBoard()[row++][col] = Token::ValkyrieToken;
    getBoard()[row++][col++] = Token::ValkyrieToken;

    //place InterceptorToken (2 spots)
    row = 0;
    getBoard()[row++][col] = Token::InterceptorToken;
    getBoard()[row++][col] = Token::InterceptorToken;

}//end placeShips


/* Plays a turn for the player */
void ComputerPlayer::playTurn(const vector<Player *> &others) const {
    /* determine randomly which player to shoot at */
    int i = rand() % others.size();

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
