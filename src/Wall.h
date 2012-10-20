#pragma once
#ifndef __WALL_H__
#define __WALL_H__

#include <SDL.h>
#include "GameObject.h"

class Wall : public GameObject {
public:
    Wall(int x, int y) : GameObject(x, y) { setType(WALL); setMove(STAND); }
    virtual void update(double diff) { };
private:

};

#endif