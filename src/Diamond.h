#pragma once
#ifndef __DIAMOND_H__
#define __DIAMOND_H__

#include <SDL.h>
#include "GameObject.h"

class Diamond : public GameObject{
public:
    Diamond(int x, int y) : GameObject(x, y) { setType(DIAMOND); setMove(STAND); }
    virtual void update(double diff) { };
private:

};

#endif