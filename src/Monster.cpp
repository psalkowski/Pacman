#include "Monster.h"
#include <iostream>


void Monster::update(double diff) {
    double ds = getNextPosition(diff);

    switch(getMove()) { 
        case LEFT:  setVelocity(-2.0); goLeft(ds);   break;
        case RIGHT: setVelocity(2.0); goRight(ds);  break;
        case DOWN:  setVelocity(2.0); goDown(ds);   break;
        case UP:    setVelocity(-2.0); goUp(ds);     break;
    }
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

void Monster::goRight(double s) {
    if(s >= Config::WIN_W)
        s = 0;

    setRect(s, getRect()->y);
}

void Monster::goLeft(double s) {
    if(s < 1)
        s = Config::WIN_W;

    setRect(s, getRect()->y);
}

void Monster::goUp(double s) {
    setRect(getRect()->x, s);
}

void Monster::goDown(double s) {
    setRect(getRect()->x, s);
}