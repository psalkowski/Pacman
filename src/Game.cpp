#include "Game.h"

Game::Game() {
    m_diff = 0;
    is_done = false;
}

Game::~Game() { 
    SDL_FreeSurface(m_screen);
    SDL_Quit();
}

void Game::initGraph() {
    /* Initialize SDL */
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        return;
    }
    m_screen = SDL_SetVideoMode(Config::WIN_W, Config::WIN_H, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
}

void Game::run() {
    initGraph();
    
    m_map = new Map(m_screen);
    m_map->convertFileToMap("level/level-1.txt");

    while(!isDone()) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_done = true;
                break;
            }
        }

        /*size_t last_ticks = SDL_GetTicks();

        // time update
        size_t ticks = SDL_GetTicks();
        m_diff = (ticks - last_ticks) / 1000.0;
        last_ticks = ticks;*/

        clear();

        m_map->draw();

        updateScreen();

        SDL_Delay(70);
    }
}

void Game::clear() {
    SDL_FillRect(m_screen, NULL, 0x000000);
}

void Game::updateScreen() {
    SDL_Flip(m_screen);
}