#pragma once
#ifndef __GAME_H__
#define __GAME_H__

#include <SDL/SDL.h>
#include "Map.h"
#include "Player.h"
#include <iostream>
#include <sstream>
#include <SDL/SDL_ttf.h>

using namespace std;

class Game {
public:
    Game();
    ~Game();
    void run();
    void processEvent();
    void setDone(bool done) { is_done = done; }

    bool isDone() { return is_done; }

private:

    void initGraph();
    void clear();
    void updateScreen();

    SDL_Surface *m_screen;
    Map *m_map;
    Player *m_player;

    SDL_Surface *m_text;

    double m_diff;
    bool is_done;
};

#endif
