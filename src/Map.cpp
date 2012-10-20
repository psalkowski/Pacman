#include "Map.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>

Map::Map() {
    m_wall = m_diamond = NULL;
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

void Map::addGameObject(GameObject *m_pole) {
    m_map.push_back(m_pole);
}

GameObject* Map::getGameObject(int index) { 
    //if(index <= m_map.size())
    
    return m_map.at(index); // jak sie zabezpieczyc tutaj przed wyjsciem poza rozmiar wektora?
}

void Map::initMap() {
    m_diamond = SDL_LoadBMP("images/diamond.bmp");
    m_wall = SDL_LoadBMP("images/block.bmp");
    m_player = SDL_LoadBMP("images/pacman.bmp");

    if(m_player == NULL || m_diamond == NULL || m_wall == NULL) {
        cout << "Z�a �cie�ka zdj��. Poprawna to /images/ " << endl;
    }

    int colorkey = SDL_MapRGB(m_screen->format, 255, 0, 255);
    SDL_SetColorKey(m_diamond, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(m_player, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
}

// funkcja nie jest bezpieczna, nale�y j� przerobi�
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
                    addGameObject(new Wall(col*30, row*30));
                else if(line.at(i) == '1')
                    addGameObject(new Diamond(col*30, row*30));
                else if(line.at(i) == 'P') {
                    addPlayer(new Player(col*30, row*30));
                }
                col++;
            }

            col = 0;
            row++;
        }
    }
    file.close();
}

void Map::update(double diff) {
    getPlayer()->update(diff);
}

void Map::draw() {
    for(unsigned i = 0; i < m_map.size(); i++) {
        GameObject *gameObject = m_map.at(i);
        switch(gameObject->getType()) {
            case WALL:
                SDL_BlitSurface(m_wall, NULL, m_screen, gameObject->getRect());
                break;
            case DIAMOND:
                SDL_BlitSurface(m_diamond, NULL, m_screen, gameObject->getRect());
                break;
            /*case PLAYER:
                Player *player = getPlayer();
                SDL_BlitSurface(m_player, player->getAnimationRect(), m_screen, player->getRect());
                break;*/
        }
    }
    SDL_BlitSurface(m_player, getPlayer()->getAnimationRect(), m_screen, getPlayer()->getRect());
}