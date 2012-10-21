#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SDL.h>
#include <iostream>
#include "GameObject.h"
#include "Monster.h"

using namespace std;
 
class Player : public Monster {
public:
    Player(double x, double y);

    virtual void update(double diff);

    SDL_Rect *getAnimationRect() { return &m_animation; }

    void updateAnimation(Move move);

private:
    void initAnimation();

    static const int m_width = 33;
    static const int m_height = 33;

    SDL_Rect m_animation;
    double m_time;

};

#endif