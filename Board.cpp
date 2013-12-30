/*
Brooks Kindle
brooks.kindle@wsu.edu

Board.cpp   -   source file for Board class
*/

#include "Board.h"

/* constructs the board with the given size */
Board::Board(unsigned int rows, unsigned int columns)
:_board(nullptr), _rows(0), _columns(0) {
    initialize(rows, columns);
}//end constructor


/* constructs the board from another board */
Board::Board(const Board &cpy) :_board(nullptr), _rows(0), _columns(0) {
    copy(cpy._board, cpy.rows(), cpy.columns());
}//end copy constructor


/* Overloaded assignment operator */
Board &Board::operator=(const Board &toCopy) {
    if(this != &toCopy) { //avoid self-assignment
        copy(toCopy._board, toCopy.rows(), toCopy.columns());
    }
    return *this;
}//end operator=


/* destructs the board */
Board::~Board() {
    uninitialize();
}//end destructor


/* Returns the rows of the board */
unsigned int Board::rows() const {
    return _rows;
}//end rows


/* Returns the columns of the board */
unsigned int Board::columns() const {
    return _columns;
}//end columns


/* Returns the given (unmodifiable) row of the board. Does not perform
bounds checking */
const token_t *const Board::operator[](int i) const {
    return _board[i];
}//end operator[]


/* Returns the given (modifiable) row of the board. Does not
perform bounds checking */
token_t *const Board::operator[](int i) {
    return _board[i];
}//end operator[]


/* Returns the token at the given coordinate */
token_t Board::operator[](Coordinate c) const {
    return _board[c.row][c.col];
}//end operator[]


/* Returns the token at the given coordinate */
token_t &Board::operator[](Coordinate c) {
    return _board[c.row][c.col];
}//end operator[]


/* Returns true if the given coordinate is within the boundaries of the board.
Return false otherwise */
bool Board::valid(Coordinate c) const {
    return c.row < rows() && c.col < columns();
}//end valid


/* Allocates memory for the game board and initializes all areas
to the default space token */
void Board::initialize(unsigned int rows, unsigned int columns) {
    if(_board) {
        uninitialize();
    }

    //begin by allocating memory for our game board
    _rows = rows;
    _columns = columns;
    _board = new token_t *[_rows]; //create rows

    for(int i = 0; i < _rows; i++) {
        _board[i] = new token_t[_columns]; //create columns
        for(int j = 0; j < _columns; j++) {
            _board[i][j] = token_t::space;//initialize coordinate to space token
        }//end for j
    }//end for i
}//end initialize


/* Deallocates memory for the game board and resets rows and columns to 0 */
void Board::uninitialize() {
    if(_board) { //need to uninitialize board
        for(int i = 0; i < _rows; i++) {
            delete _board[i]; //delete row
            _board[i] = nullptr;
        }//end for i
        delete _board;
        _board = nullptr;
        _rows = 0;
        _columns = 0;
    }//end if
}//end uninitialize


/* Changes the board to be an exact (deep) copy of the inputted board */
void Board::copy(token_t **const board, unsigned int nRows, unsigned int nCols) {
    if(_board != board) { //prevent self-copy
        if(_rows != nRows && _columns != nCols) { //unequal dimensions
            uninitialize(); //delete old board
            initialize(nRows, nCols); //initialize new board with correct size
        }//end if

        for(int i = 0; i < rows(); i++) {
            for(int j = 0; j < columns(); j++) {
                _board[i][j] = board[i][j]; //copy values into our new board
            }//end for j
        }//end for i

    }//end if
}//end copy