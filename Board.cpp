/*
Brooks Kindle
brooks.kindle@wsu.edu

Board.cpp   -   source file for Board class
*/

#include "Board.h"
using std::vector;

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
const Token *const Board::operator[](int i) const {
    return _board[i];
}//end operator[]


/* Returns the given (modifiable) row of the board. Does not
perform bounds checking */
Token *const Board::operator[](int i) {
    return _board[i];
}//end operator[]


/* Returns the token at the given coordinate */
Token Board::operator[](Coordinate c) const {
    return _board[c.row][c.col];
}//end operator[]


/* Returns the token at the given coordinate */
Token &Board::operator[](Coordinate c) {
    return _board[c.row][c.col];
}//end operator[]


/* Returns true if the given coordinate is within the boundaries of the board.
Return false otherwise */
bool Board::valid(Coordinate c) const {
    return c.row < rows() && c.col < columns();
}//end valid


/* Returns true if the given coordinates are within the boundaries of the board */
bool Board::valid(Coordinate c, Direction d, unsigned int len) const {
    auto coords = generateCoordinates(c, d, len);
    for(Coordinate c : coords) {
        if(!valid(c)) {
            return false;
        }
    }
    return true;
}//end valid


/* Returns true if the given coordinate is valid and 
occupied by something other than the space token */
bool Board::contains(Token t, Coordinate c) const {
    return valid(c) && (*this)[c.row][c.col] == t;
}//end contains


/* Returns true if the given coordinates are valid and
occupied by something other than the space token */
bool Board::contains(Token t, Coordinate c, Direction d, unsigned int len) const {
    for(Coordinate c : generateCoordinates(c, d, len)) {
        if(!contains(t, c)) {
            return false;
        }
    }
    return true;
}//end contains


/* Allocates memory for the game board and initializes all areas
to the default SpaceToken token */
void Board::initialize(unsigned int rows, unsigned int columns) {
    if(_board) {
        uninitialize();
    }

    //begin by allocating memory for our game board
    _rows = rows;
    _columns = columns;
    _board = new Token *[_rows]; //create rows

    for(int i = 0; i < _rows; i++) {
        _board[i] = new Token[_columns]; //create columns
        for(int j = 0; j < _columns; j++) {
            _board[i][j] = Token::SpaceToken;//initialize coordinate to SpaceToken token
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
void Board::copy(Token **const board, unsigned int nRows, unsigned int nCols) {
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


/* Returns a vector of coordinates starting from the given coordinate
and going in a direction for a certain length. For example, if the coordinate
was (0,0), the direction South, and the length 3, then the vector
would contain the coordinates (0,0), (1,0), (2,0) */
vector<Coordinate> Board::generateCoordinates(Coordinate c, Direction d,
                                              unsigned int len) const {
    vector<Coordinate> coords;

    /* Step 1: Determine the row and column offset 
    for each successive coordinate we generate */
    int rowOffset = 0, //row offset for the direction we're going
        colOffset = 0; //column offset

    if(d & North) { //direction is north
        rowOffset -= 1;
    }
    if(d & South) { //direction is south
        rowOffset += 1;
    }
    if(d & East) { //direction is east
        colOffset += 1;
    }
    if(d & West) { //direction is west
        colOffset -= 1;
    }

    /* Step 2: Generate each coordinate and push it to our result vector */
    for(int i = 0; i < len; i++) {
        coords.push_back(c);
        c.row += rowOffset;
        c.col += colOffset;
    }//end for

    return coords;
}//end generateCoordinates
