/*
Brooks Kindle
brooks.kindle@wsu.edu

Board.h -   header file for Board class
*/

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Tokens.h"
#include "Coordinate.h"
#include "Direction.h"

/* player's game board that the game is played out on */
class Board {
    public:
        Board(unsigned int rows, unsigned int columns);
        Board(const Board &);
        Board &operator=(const Board &);
        ~Board();
        unsigned int rows() const;
        unsigned int columns() const;

        const Token *const operator[](int) const;
        Token *const operator[](int);
        Token operator[](Coordinate) const;
        Token &operator[](Coordinate);

        bool valid(Coordinate c) const;
        bool valid(Coordinate c, Direction d, unsigned int len) const;
        bool contains(Token t, Coordinate c) const;
        bool contains(Token t, Coordinate c, Direction d, unsigned int len) const;
        bool place(Token t, Coordinate c);
        bool place(Token t, Coordinate c, Direction d, unsigned int len);
    private:
        Token **_board;
        unsigned int _rows;
        unsigned int _columns;

        void initialize(unsigned int rows, unsigned int columns);
        void uninitialize();
        void copy(Token **const board, unsigned int nRows, unsigned int nCols);
        std::vector<Coordinate> generateCoordinates(Coordinate c, Direction d, 
                                                    unsigned int len) const;

};//end Board

#endif
