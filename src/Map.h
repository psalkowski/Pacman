#pragma once
#ifndef __MAP_H__
#define __MAP_H__

#include "Config.h"
#include "Player.h"
#include "Ghost.h"
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

    
private:
    vector<GameObject*> m_vector_cross;
    vector<GameObject*> m_vector_wall;
    vector<GameObject*> m_vector_diamond;
    vector<Ghost*> m_vector_ghosts;
   
    void initMap();
    
    bool isCross(Ghost *ghost);

    void addPlayer(Player *_player) { player = _player; }
    void addGhost(Ghost *ghost) { m_vector_ghosts.push_back(ghost); }
    void addWall(GameObject *gameObject) { m_vector_wall.push_back(gameObject); }
    void addDiamond(GameObject *gameObject) {m_vector_diamond.push_back(gameObject); }
    void addCross(GameObject* gameObject) { m_vector_cross.push_back(gameObject); }

    void destroyObject(GameObject *object);

    GameObject *getGameObject(int index);

    bool getColision(SDL_Rect *rectA, SDL_Rect *rectB, int radiusA, int radiusB);
    bool getColisionsWithWall(Monster *monster, double diff);
    GameObject* getPlayerColisions(Type type, double diff);

    Player *player;
    SDL_Surface *m_wall;
    SDL_Surface *m_diamond;
    SDL_Surface *m_player;
    SDL_Surface *m_ghost;

    SDL_Surface *m_screen;
};

#endif
