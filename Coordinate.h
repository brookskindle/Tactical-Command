/*
Brooks Kindle
brooks.kindle@wsu.edu

Coordinate.h    -   header file for Coordinate struct
*/

#ifndef COORDINATE_H
#define COORDINATE_H

/* Represents a 2D location on a row-column plane */
struct Coordinate {
    unsigned int row;
    unsigned int col;
    Coordinate(unsigned int row, unsigned int col):row(row), col(col) {}
    Coordinate() :row(0), col(0) {}
};//end Coordinate

#endif
