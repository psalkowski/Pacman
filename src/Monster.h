#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include <SDL.h>
#include "GameObject.h"

enum Move {
    LEFT    = 0,
    RIGHT   = 1,
    UP      = 2,
    DOWN    = 3,
    STAND   = 4
};

class Monster : public GameObject {
public:
    Monster(Type type, int x, int y) : GameObject(type, x, y) { setDefaultPos(x, y); };

    Move getMove() { return m_move; }
    double getVelocity() { return m_velocity; }
    double getNextPosition(double diff);
    SDL_Rect getDefaultPos() { return m_def_pos; }

    void setMove(Move move) { m_move = move; }
    void setVelocity(double velocity) { m_velocity = velocity; }
    
    void resetPos() { setRect(m_def_pos.x, m_def_pos.y); }
    void setDefaultPos(double x, double y) { m_def_pos.x = x; m_def_pos.y = y; }

    void goRight(double s);
    void goLeft(double s);
    void goUp(double s);
    void goDown(double s);

    virtual void update(double diff);

private:
    Move m_move;
    double m_velocity;

    SDL_Rect m_def_pos;
};

#endif