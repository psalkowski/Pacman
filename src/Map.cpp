#include "Map.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>

Map::Map() {
    m_wall = m_diamond = m_ghost = NULL;
    initMap();
}

Map::Map(SDL_Surface *screen) {
    setScreenSurface(screen);
    m_player = m_wall = m_diamond = NULL;
    initMap();
}

Map::~Map() {
    SDL_FreeSurface(m_diamond);
    SDL_FreeSurface(m_wall);
    SDL_FreeSurface(m_player);
}

void Map::setScreenSurface(SDL_Surface *screen) {
    m_screen = screen; 
}

void Map::initMap() {
    m_diamond = SDL_LoadBMP("images/diamond.bmp");
    m_wall = SDL_LoadBMP("images/block.bmp");
    m_player = SDL_LoadBMP("images/pacman.bmp");
    m_ghost = SDL_LoadBMP("images/ghost.bmp");

    if(m_player == NULL || m_diamond == NULL || m_wall == NULL || m_ghost == NULL) {
        cout << "Z³a œcie¿ka zdjêæ. Poprawna to /images/ " << endl;
    }

    int colorkey = SDL_MapRGB(m_screen->format, 255, 0, 255);
    SDL_SetColorKey(m_diamond, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(m_player, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(m_ghost, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
}

// funkcja nie jest bezpieczna, nale¿y j¹ przerobiæ
void Map::convertFileToMap(string source) {
    fstream file;
    string line;
    int row = 0, col = 0;

    file.open(source);

    if(file.is_open()) {
        while(!file.eof()) {
            getline(file, line);
            for(unsigned i = 0; i < line.length(); i++) {
                if(line.at(i) == '0')
                    addWall(new GameObject(WALL, col*30, row*30));
                else if(line.at(i) == '1')
                    addDiamond(new GameObject(DIAMOND, col*30, row*30));
                else if(line.at(i) == 'P')
                    addPlayer(new Player(col*30, row*30));
                else if(line.at(i) == 'G')
                    addGhost(new Ghost(col*30, row*30));
                else if(line.at(i) == 'C') {
                    addDiamond(new GameObject(DIAMOND, col*30, row*30));
                    addCross(new GameObject(CROSS, col*30, row*30));
                }
                col++;
            }

            col = 0;
            row++;
        }
    }
    file.close();
}
void Map::destroyObject(GameObject *object) {
    if(object->getType() == GHOST) {
        vector<Ghost*>::iterator iter = m_vector_ghosts.begin();
        vector<Ghost*>::iterator endIter = m_vector_ghosts.end();

        for(int i = 0; iter != endIter; iter++, i++) {
            if(m_vector_ghosts.at(i) == object) {
                m_vector_ghosts.erase(iter);
                return;
            }
        }
    }

    if(object->getType() == DIAMOND) {
        vector<GameObject*>::iterator iter = m_vector_diamond.begin();
        vector<GameObject*>::iterator endIter = m_vector_diamond.end();

        for(int i = 0; iter != endIter; iter++, i++) {
            if(m_vector_diamond.at(i) == object) {
                m_vector_diamond.erase(iter);
                return;
            }
        }
    }
    
}
void Map::update(double diff) {
    GameObject* diamond = getPlayerColisions(DIAMOND, diff);
    if(diamond != NULL)
        destroyObject(diamond);

    for(int i = 0; i < m_vector_ghosts.size(); i++) {
        Ghost *ghost = m_vector_ghosts.at(i);
        bool check = false;
        if(isCross(ghost))
            ghost->setMove(ghost->getRandomMove());

        while(getColisionsWithWall(ghost, diff)) {
            ghost->setMove(ghost->getRandomMove());
        }

        ghost->update(diff);
    }
    
    GameObject* ghost = getPlayerColisions(GHOST, diff);
    if(ghost != NULL)
        destroyObject(ghost);

    if(getColisionsWithWall(player, diff))
        player->setMove(STAND);
    player->update(diff);
}

void Map::draw() {
    for(unsigned i = 0; i < m_vector_wall.size(); i++) {
        GameObject *gameObject = m_vector_wall.at(i);
        SDL_BlitSurface(m_wall, NULL, m_screen, gameObject->getRect());
    }

    for(unsigned i = 0; i < m_vector_diamond.size(); i++) {
        GameObject *gameObject = m_vector_diamond.at(i);
        SDL_BlitSurface(m_diamond, NULL, m_screen, gameObject->getRect());
    }
    for(unsigned i = 0; i < m_vector_ghosts.size(); i++) {
        Ghost *ghost = m_vector_ghosts.at(i);
        SDL_BlitSurface(m_ghost, NULL, m_screen, ghost->getRect());
    }

    SDL_BlitSurface(m_player, getPlayer()->getAnimationRect(), m_screen, getPlayer()->getRect());
}

GameObject* Map::getPlayerColisions(Type type, double diff) {
    SDL_Rect plrRect = *player->getRect();
    vector<GameObject*> vector_type;

    int radius;
    if(type == GHOST)
        radius = 10;
    else radius = 5;

    switch(player->getMove()) { 
        case LEFT:  plrRect.x = player->getNextPosition(diff);  break;
        case RIGHT: plrRect.x = player->getNextPosition(diff);  break;
        case DOWN:  plrRect.y = player->getNextPosition(diff);  break;
        case UP:    plrRect.y = player->getNextPosition(diff);  break;
    }

    switch(type) {
        case DIAMOND: vector_type = m_vector_diamond; break;
        case GHOST: 
            for(int i = 0; i < m_vector_ghosts.size(); i++)
                vector_type.push_back(m_vector_ghosts.at(i)); 
            break;
    }

    for(unsigned i = 0; i < vector_type.size(); i++) {
        GameObject *gameObject = vector_type.at(i);


        if(plrRect.x - 15 == gameObject->getRect()->x + radius && 
            plrRect.y + 15 >= gameObject->getRect()->y - radius &&
            plrRect.y - 15 <= gameObject->getRect()->y + radius)

            return gameObject;

        if(plrRect.x + 15 == gameObject->getRect()->x - radius && 
            plrRect.y + 15 >= gameObject->getRect()->y - radius &&
            plrRect.y - 15 <= gameObject->getRect()->y + radius)

            return gameObject;

        if(plrRect.y - 15== gameObject->getRect()->y + radius &&
            plrRect.x + 15 >= gameObject->getRect()->x - radius &&
            plrRect.x - 15 <= gameObject->getRect()->x + radius)

            return gameObject;

        if(plrRect.y + 15 == gameObject->getRect()->y - radius &&
            plrRect.x + 15 >= gameObject->getRect()->x - radius &&
            plrRect.x - 15 <= gameObject->getRect()->x + radius)

            return gameObject;

    }

    return NULL;
}
bool Map::getColisionsWithWall(Monster *monster, double diff) {
    SDL_Rect monsterRect = *monster->getRect();

    int radius, objRadius;
    if(monster->getType() == PLAYER) {
        radius = 10;
        objRadius = 15;
    } else if(monster->getType() == GHOST) {
        radius = 14;
        objRadius = 15;
    }
    // wczytanie kolejnego ruchu
    switch(monster->getMove()) { 
        case LEFT:  monsterRect.x = monster->getNextPosition(diff);  break;
        case RIGHT: monsterRect.x = monster->getNextPosition(diff);  break;
        case DOWN:  monsterRect.y = monster->getNextPosition(diff);  break;
        case UP:    monsterRect.y = monster->getNextPosition(diff);  break;
    }

    // sprawdzanie kolizji
    for(unsigned i = 0; i < m_vector_wall.size(); i++) {
        GameObject *gameObject = m_vector_wall.at(i);

        switch(monster->getMove()) {
            case LEFT: 
                if(monsterRect.x - radius == gameObject->getRect()->x + objRadius && 
                    monsterRect.y + radius >= gameObject->getRect()->y - objRadius &&
                    monsterRect.y - radius <= gameObject->getRect()->y + objRadius)

                    return true;
                break;
            case RIGHT: 
                if(monsterRect.x + radius == gameObject->getRect()->x - objRadius && 
                    monsterRect.y + radius >= gameObject->getRect()->y - objRadius &&
                    monsterRect.y - radius <= gameObject->getRect()->y + objRadius)

                    return true;
                break;
            case UP: 
                if(monsterRect.y - radius == gameObject->getRect()->y + objRadius &&
                    monsterRect.x + radius >= gameObject->getRect()->x - objRadius &&
                    monsterRect.x - radius <= gameObject->getRect()->x + objRadius)

                    return true;
                break;
            case DOWN: 
                if(monsterRect.y + radius == gameObject->getRect()->y - objRadius &&
                    monsterRect.x + radius >= gameObject->getRect()->x - objRadius &&
                    monsterRect.x - radius <= gameObject->getRect()->x + objRadius)

                    return true;
                break;
        }
    }

    return false;
}

bool Map::isCross(Ghost *ghost) {
    for(unsigned i = 0; i < m_vector_cross.size(); i++) {
        GameObject *gameObject = m_vector_cross.at(i);

        switch(ghost->getMove()) {
            case LEFT: 
                if(ghost->getRect()->x == gameObject->getRect()->x && 
                    ghost->getRect()->y + 14 >= gameObject->getRect()->y - 15 &&
                    ghost->getRect()->y - 14 <= gameObject->getRect()->y + 15)

                    return true;
                break;
            case RIGHT: 
                if(ghost->getRect()->x == gameObject->getRect()->x && 
                    ghost->getRect()->y + 14 >= gameObject->getRect()->y - 15 &&
                    ghost->getRect()->y - 14 <= gameObject->getRect()->y + 15)

                    return true;
                break;
            case UP: 
                if(ghost->getRect()->y == gameObject->getRect()->y &&
                    ghost->getRect()->x + 14 >= gameObject->getRect()->x - 15 &&
                    ghost->getRect()->x - 14 <= gameObject->getRect()->x + 15)

                    return true;
                break;
            case DOWN: 
                if(ghost->getRect()->y == gameObject->getRect()->y &&
                    ghost->getRect()->x + 14>= gameObject->getRect()->x - 15 &&
                    ghost->getRect()->x - 14 <= gameObject->getRect()->x + 15)

                    return true;
                break;
        }
    }

    return false;
}