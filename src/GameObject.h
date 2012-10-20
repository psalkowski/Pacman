#pragma once
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <SDL.h>
#include "Config.h"

enum Type {
    NONE,
    WALL,
    DIAMOND,
    EXTRA_DIAMOND,
    MONSTER,
    PLAYER
};

enum Move {
    LEFT    = 0,
    RIGHT   = 1,
    UP      = 2,
    DOWN    = 3,
    STAND   = 4
};

class GameObject {
public:
    GameObject(double x, double y) { m_dimension = new SDL_Rect(); setRect(x, y); }
    GameObject(SDL_Rect *rect) { m_dimension = rect; }

    int getRangeToPlayer() { return rangeToPlayer; }
    Move getMove() { return move; }
    Type getType() { return type; }
    SDL_Rect* getRect() { return m_dimension; }
    double getVelocity() { return velocity; }

    void setRect(SDL_Rect *rect) { m_dimension = rect; }
    void setRect(double x, double y) { m_dimension->x = x; m_dimension->y = y; }
    //void setRect(int x, int y, int width, int height) { setRect(x, y); m_dimension->w = width; m_dimension->h = height; }
    void setType(Type m_type) { type = m_type; }
    void setMove(Move m_move) { move = m_move; }
    void setVelocity(double m_velocity) { velocity = m_velocity; }

    virtual void update(double diff) { };
private:
    int rangeToPlayer;

    SDL_Rect *m_dimension;
    Type type;
    Move move;

    double velocity;
};

#endif