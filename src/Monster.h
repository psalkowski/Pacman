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
    Monster(Type type, int x, int y) : GameObject(type, x, y) { };

    Move getMove() { return m_move; }
    double getDiff() { return m_diff; }
    double getVelocity() { return m_velocity; }

    double getNextPosition(double diff);

    void setDiff(int diff) { m_diff = diff; }
    void setMove(Move move) { m_move = move; }
    void setVelocity(double velocity) { m_velocity = velocity; }

    void goRight(double s);
    void goLeft(double s);
    void goUp(double s);
    void goDown(double s);

    virtual void update(double diff) {}

private:
    Move m_move;
    double m_diff;
    double m_velocity;
};

#endif