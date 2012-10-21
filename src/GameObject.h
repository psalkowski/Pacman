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

class GameObject {
public:
    GameObject(Type type, double x, double y) { m_type = type; m_dimension = new SDL_Rect(); setRect(x, y); }
    GameObject(Type type, SDL_Rect *rect) { m_type = type; m_dimension = rect; }

    int getRangeToPlayer() { return rangeToPlayer; }
    
    Type getType() { return m_type; }
    SDL_Rect* getRect() { return m_dimension; }

    void setRect(SDL_Rect *rect) { m_dimension = rect; }
    void setRect(double x, double y) { m_dimension->x = x; m_dimension->y = y; }
    void setType(Type type) { m_type = type; }
private:
    int rangeToPlayer;

    SDL_Rect *m_dimension;
    Type m_type;
};

#endif