#pragma once
#ifndef __GHOST_H__
#define __GHOST_H__

#include <SDL/SDL.h>
#include <cstdlib> 
#include "Monster.h"

class Ghost : public Monster {
public:
    Ghost(int x, int y) : Monster(GHOST, x, y) { setMove(getRandomMove()); m_time = 0; };

    Move getRandomMove();
private:
    double m_time;
};

#endif
