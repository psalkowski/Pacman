#include "Monster.h"
#include <iostream>

void Monster::goRight(double s) {
    if(s >= Config::WIN_W)
        s = 0;
    setRect(s, getRect()->y);
}

void Monster::goLeft(double s) {
    if(s < 1)
        s = Config::WIN_W;

    std::cout << s << std::endl;
    setRect(s, getRect()->y);
}

void Monster::goUp(double s) {
    setRect(getRect()->x, s);
}

void Monster::goDown(double s) {
    setRect(getRect()->x, s);
}

double Monster::getNextPosition(double diff) {
    switch(getMove()) {
        case LEFT:
            return getRect()->x + getVelocity() * diff;
        case RIGHT:
            return getRect()->x + getVelocity() * diff + 1; // +1, bo SDL_Rect x jest liczba calkowita, czyli zaokrlaga
        case UP:
            return getRect()->y + getVelocity() * diff;
        case DOWN:
            return getRect()->y + getVelocity() * diff + 1;
    }

    return 0;
}