/*
Brooks Kindle
brooks.kindle@wsu.edu

util.cpp    -   source file for util namespace
*/

#include <iostream>
#include <limits>
#include "util.h"
using std::cout;
using std::cin;

/* waits for the user to press enter before returning */
void util::pressEnterToContinue() {
    cout << "Press <enter> to continue.\n" << std::flush;
    cin.sync();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}//end pressEnterToContinue
