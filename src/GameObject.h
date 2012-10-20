#ifndef __POLE_H__
#define __POLE_H__

#include <SDL.h>

enum Field {
    NONE,
    WALL,
    DIAMOND,
    EXTRA_DIAMOND
};

class GameObject {
public:
    GameObject() { setField(NONE); }
    GameObject(int x, int y) { setField(NONE); setRect(x, y); }
    GameObject(Field field) { setField(field); }
    GameObject(Field field, int x, int y) { setField(field); setRect(x, y); }
    GameObject(SDL_Rect rect) { setField(NONE); m_dimension = rect; }

    int getRangeToPlayer() { return rangeToPlayer; }
    bool canLeft() { return can_left; }
    bool canRight() { return can_right; }
    bool canUp() { return can_up; }
    bool canDown() { return can_down; }
    Field getField() { return field; }
    SDL_Rect* getRect() { return &m_dimension; }
    
    void setRect(SDL_Rect rect) { m_dimension = rect; }
    void setRect(int x, int y) { m_dimension.x = x; m_dimension.y = y; }
    void setRect(int x, int y, int width, int height) { setRect(x, y); m_dimension.w = width; m_dimension.h = height; }
    void setField(Field m_field) {field = m_field; }

private:
    int rangeToPlayer;
    
    SDL_Rect m_dimension;
    Field field;
    bool can_left;
    bool can_right;
    bool can_up;
    bool can_down;
};

#endif