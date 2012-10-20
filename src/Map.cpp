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
    m_wall = m_diamond = NULL;
    initMap();
}

Map::~Map() {
    SDL_FreeSurface(m_diamond);
    SDL_FreeSurface(m_wall);
    //SDL_FreeSurface(m_pacman);
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

    if(m_diamond == NULL || m_wall == NULL) {
        cout << "error! " << endl;
    }

    int colorkey = SDL_MapRGB(m_screen->format, 255, 0, 255);
    SDL_SetColorKey(m_diamond, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
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
                GameObject *gameObject = new GameObject(col*30, row*30);

                switch(line.at(i)) {
                    case '0':
                        gameObject->setField(WALL);
                        break;
                    case '1':
                        gameObject->setField(DIAMOND);
                        break;
                    default:
                        break;
                }

                addGameObject(gameObject);
                col++;
            }

            col = 0;
            row++;
        }
    }
    file.close();
}

void Map::draw() {
    for(unsigned i = 0; i < m_map.size(); i++) {
        GameObject *gameObject = m_map.at(i);
        if(gameObject->getField() == WALL)
            SDL_BlitSurface(m_wall, NULL, m_screen, gameObject->getRect());
        else if(gameObject->getField() == DIAMOND)
            SDL_BlitSurface(m_diamond, NULL, m_screen, gameObject->getRect());
    }
}