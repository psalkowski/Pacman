#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SDL.h>
#include <iostream>
#include "GameObject.h"

using namespace std;
 
class Player : public GameObject {
public:
    Player(double x, double y);

    virtual void update(double diff);
    SDL_Rect *getAnimationRect() { return &m_animation; }

    double getNextPosition(double diff);

    void updateAnimation(Move move);
    
    void goRight(double s);
    void goLeft(double s);
    void goUp(double s);
    void goDown(double s);

private:
    void initAnimation();

    static const int m_width = 33;
    static const int m_height = 33;

    SDL_Rect m_animation;
    double m_time;

};

#endif