#ifndef __MAP_H__
#define __MAP_H__

#include "GameObject.h"
#include "Config.h"
#include <string>
#include <vector>

using namespace std;

class Map {
public:
    Map();
    Map(SDL_Surface *screen);
    ~Map();
    void draw();
    //SDL_Surface *getMapSurface() { return mapa; }
    void convertFileToMap(string source);
    void setScreenSurface(SDL_Surface *screen);

private:
    vector<GameObject*> m_map;
    void initMap();
    void addGameObject(GameObject *gameObject);
    GameObject *getGameObject(int index);

    SDL_Surface *m_wall;
    SDL_Surface *m_diamond;

    SDL_Surface *m_screen;
};

#endif