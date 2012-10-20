#ifndef __GAME_H__
#define __GAME_H__

#include <SDL.h>
#include "Map.h"
#include <iostream>

using namespace std;

class Game {
public:
    Game();
    ~Game();
    void run();
    void initGraph();
    void setDone(bool done) { is_done = done; }

    bool isDone() { return is_done; }

private:
    //void initGraph();
    void clear();
    void updateScreen();

    SDL_Surface *m_screen;
    Map *m_map;
    double m_diff;
    bool is_done;
};

#endif