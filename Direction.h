/*
Brooks Kindle
brooks.kindle@wsu.edu

Direction.h -   contains Direction enum
*/

#ifndef DIRECTION_H
#define DIRECTION_H

/* An enumeration that identifies valid directions that ships can be placed
on the board. Directions can be combined using the bitwise or operator.
For Example:
    North | East would be equivalent of saying the direction is NorthEast
    East | West does nothing at all (EastWest doesn't many any sense, does it?)
    SouthWest | West is equivalent to saying SouthWest
    SouthEast is equivalent to South | East
*/
enum Direction {
    North       =   1<<3,           //0000 1000 
    South       =   1<<2,           //0000 0100 
    East        =   1<<1,           //0000 0010 
    West        =   1<<0,           //0000 0001 

    NorthWest   =   North | West,   //0000 1001
    NorthEast   =   North | East,   //0000 1010
    SouthWest   =   South | West,   //0000 0101
    SouthEast   =   South | East,   //0000 0110
};//end Direction

#endif