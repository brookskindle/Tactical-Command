/*
Brooks Kindle
brooks.kindle@wsu.edu

Board.h -   header file for Board class
*/

#ifndef BOARD_H
#define BOARD_H

#include "Tokens.h"

/* player's game board that the game is played out on */
class Board {
    public:
        Board(unsigned int rows, unsigned int columns);
        Board(const Board &);
        Board &operator=(const Board &);
        ~Board();
        unsigned int rows() const;
        unsigned int columns() const;
        const token_t *const operator[](int) const;
        token_t *const operator[](int);
    private:
        token_t **_board;
        unsigned int _rows;
        unsigned int _columns;

        void initialize(unsigned int rows, unsigned int columns);
        void uninitialize();
        void copy(token_t **const board, unsigned int nRows, unsigned int nCols);
};//end Board

#endif
