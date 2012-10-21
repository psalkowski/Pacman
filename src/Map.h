#pragma once
#ifndef __MAP_H__
#define __MAP_H__

#include "Config.h"
#include "Player.h"
#include <string>
#include <vector>

using namespace std;

class Map {
public:
    Map();
    Map(SDL_Surface *screen);
    ~Map();

    Player *getPlayer() { return player; }
    
    void update(double diff);
    void draw();
    void convertFileToMap(string source);
    void setScreenSurface(SDL_Surface *screen);

    void addPlayer(Player *_player) { _player->setType(PLAYER); player = _player; }

private:
    vector<GameObject*> m_map;
    void initMap();
    void addGameObject(GameObject *gameObject);
    void destroyObject(std::vector<GameObject*> & vObject, GameObject *object);

    GameObject *getGameObject(int index);
    vector<GameObject*> getColisions(Monster *monster, double diff);

    Player *player;
    SDL_Surface *m_wall;
    SDL_Surface *m_diamond;
    SDL_Surface *m_player;

    SDL_Surface *m_screen;
};

#endif