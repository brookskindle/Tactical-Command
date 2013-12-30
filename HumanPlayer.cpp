/*
Brooks Kindle
brooks.kindle@wsu.edu

HumanPlayer.cpp -   contains HumanPlayer (class) source code
*/

#include <iostream>
#include "HumanPlayer.h"
using std::vector;
using std::cout;
using std::cin;
using std::endl;

/* Constructs the human player */
HumanPlayer::HumanPlayer() {
}//end constructor


/* Destructs the player */
HumanPlayer::~HumanPlayer() {
}//end destructor


/* Places ship tokens on the player's board */
void HumanPlayer::placeShips() {
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


/* Plays one turn of the player (which probably involves
firing shots at one of the other players) */
void HumanPlayer::playTurn(const std::vector<Player *> &others) const {
    unsigned int i = 0;
    if(others.size() != 1) {
        cout << "There are " << others.size() << " players.\n";
        cout << "Which player do you want to shoot at?\n(Enter a number between ";
        cout << "0 and " << others.size() - 1 << "): ";
        cin >> i; //get player to shoot at
    }

    cout << "Enter the row and column you wish to fire at.\n";
    cout << "Enter the numbers with a space between them: ";
    unsigned int row = 0, col = 0;
    cin >> row >> col; //get firing coordinates

    /* Shoot the bugger, Ender */
    shoot(Coordinate(row, col), *(others[i]));
}//end playTurn
