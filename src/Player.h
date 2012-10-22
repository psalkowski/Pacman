#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SDL.h>
#include <iostream>
#include "Monster.h"

using namespace std;
 
class Player : public Monster {
public:
    Player(double x, double y);

    virtual void update(double diff);
    int getLife() { return m_life; }
    void lostLife();
    
    SDL_Rect *getAnimationRect() { return &m_animation; }
    SDL_Rect getDefaultPos() { return m_def_pos; }
    
    void resetPos() { setRect(m_def_pos.x, m_def_pos.y); }
    void setDefaultPos(double x, double y) { m_def_pos.x = x; m_def_pos.y = y; }
    void updateAnimation(Move move);

private:
    void initAnimation();

    static const int m_width = 33;
    static const int m_height = 33;

    SDL_Rect m_animation;
    SDL_Rect m_def_pos;

    double m_time;
    int m_life;
};

#endif