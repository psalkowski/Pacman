#include "Ghost.h"

Move Ghost::getRandomMove() {
    switch(rand()%4) {
        case 0: return LEFT;
        case 1: return RIGHT;
        case 2: return UP;
        case 3: return DOWN;
        default:
            break;
    }
    return STAND;
}