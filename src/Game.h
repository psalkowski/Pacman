#pragma once
#ifndef __GAME_H__
#define __GAME_H__

#include <SDL.h>
#include "Map.h"
#include "Player.h"
#include <iostream>

using namespace std;

class Game {
public:
    ~Game();
    static Game *getInstance();
    void run();
    void processEvent();
    void setDone(bool done) { is_done = done; }

    bool isDone() { return is_done; }

private:
    Game();
    void initGraph();
    void clear();
    void updateScreen();

    SDL_Surface *m_screen;
    Map *m_map;
    Player *m_player;

    double m_diff;
    bool is_done;
    static Game* singleton;
};

#endif