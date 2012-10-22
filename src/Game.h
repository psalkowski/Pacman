#pragma once
#ifndef __GAME_H__
#define __GAME_H__

#include <SDL.h>
#include "Map.h"
#include "Player.h"
#include <iostream>

using namespace std;

enum Status {
    MENU,
    START,
    REPEAT,
    QUIT
};

class Game {
public:
    ~Game();
    static Game *getInstance();
    void run();
    void processEvent();
    void setStatus(Status status) { m_status = status; }
    Status getStatus() { return m_status; }
    
private:
    Game();
    void initGraph();
    void clear();
    void updateScreen();

    SDL_Surface *m_screen;
    Map *m_map;
    Player *m_player;

    double m_diff;
    Status m_status;
    static Game* singleton;
};

#endif