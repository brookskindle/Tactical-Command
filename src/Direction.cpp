/*
Brooks Kindle
brooks.kindle@wsu.edu

Direction.h -   contains Direction enum
*/

#include "Direction.h"
using std::vector;

/* Returns a vector of all directions */
vector<Direction> allDirections() {
    vector<Direction> dirs;
    dirs.push_back(North);
    dirs.push_back(South);
    dirs.push_back(East);
    dirs.push_back(West);
    return dirs;
}//end all