/*
Brooks Kindle
brooks.kindle@wsu.edu

Player.cpp  -   source file for Player class
*/

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


/* Copy constructs the player. Note, the id of the player
WILL NOT be the same as the one used to copy from */
Player::Player(const Player &cpy) :_id(ID++), _board(cpy._board) {
}//end copy constructor


/* Assignment operator */
Player &Player::operator=(const Player &toCopy) {
    if(this != &toCopy) { //avoid self-assignment
        _board = toCopy._board;
    }
    return *this;
}//end operator=


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
    /* go through each token in our board and see if a ship still exists */
    for(int i = 0; i < _board.rows(); i++) {

        for(int j = 0; j < _board.columns(); j++) {
            Token token = _board[i][j];
            if(!(token == SpaceToken || token == HitToken || token == MissToken)) {
                return false; //at least 1 ship token
            }
        }//end for j

    }//end for i

    return true; //noooooooo ship tokens
}//end dead


/* Fires a shot at another player. Return true if a HitToken, else return false */
Player::ShotType Player::shoot(Coordinate loc, Player &targ) const {
    ShotType HitToken_ = Invalid;
    if(loc.row < targ.board().rows() && //valid coordinate
       loc.col < targ.board().columns()) {

           if(targ.board()[loc.row][loc.col] != HitToken && //un-used coordinate
              targ.board()[loc.row][loc.col] != MissToken) {
                  /* determine if the shot is a HitToken or MissToken */
                  Token old = targ.board()[loc.row][loc.col];
                  HitToken_ = (old == SpaceToken) ? Miss : Hit;
                  targ._board[loc.row][loc.col] = (HitToken_) ? HitToken : MissToken;
                  /* determine if the HitToken sank a boat */
                  if(HitToken_ == Hit) {
                      HitToken_ = SinkingHit; //assume it sank the ship
                      for(int i = 0; i < _board.rows(); i++) {
                          for(int j = 0; j < _board.columns(); j++) {
                              if(_board[i][j] == old) { //HitToken ship not sunk
                                  HitToken_ = Hit;
                                  break;
                              }
                          }//end for j
                          if(HitToken_ == Hit) {
                              break;
                          }
                      }//end for i
                  }//end if(HitToken_ == Hit)
           }//end if
    }//end if
    return HitToken_;
}//end shoot


/* Returns the player's board */
Board &Player::getBoard() {
    return _board;
}//end board
