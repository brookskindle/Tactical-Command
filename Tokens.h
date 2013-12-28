/*
Brooks Kindle
brooks.kindle@wsu.edu

Tokens.h    -   header file for token types (found in the enum token_t)
*/

#ifndef TOKENS_H
#define TOKENS_H

/* contains token values for each game piece */
enum token_t {
    space, miss, hit, destroyer, frigate, crusader, valkyrie, interceptor
};
//namespace tokens {
//    const char space = '-';
//    const char hit = '*';
//    const char miss = '.';
//    const char destroyer = 'd'; //length 5 ship
//    const char frigate = 'f'; //length 4 ship
//    const char crusader = 'c'; //length 3 ship
//    const char valkyrie = 'v'; //length 3 ship
//    const char interceptor = 'i'; //length 2 ship
//};//end tokens

#endif