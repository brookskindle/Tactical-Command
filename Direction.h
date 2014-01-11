/*
Brooks Kindle
brooks.kindle@wsu.edu

Direction.h -   contains Direction enum
*/

#ifndef DIRECTION_H
#define DIRECTION_H

#include <vector>

/* An enumeration that identifies valid directions that ships can be placed
on the board */
enum Direction {
    North       =   1<<3,           //0000 1000 
    South       =   1<<2,           //0000 0100 
    East        =   1<<1,           //0000 0010 
    West        =   1<<0,           //0000 0001 
};//end Direction


std::vector<Direction> allDirections();
#endif