#include "Game.h"

Game* Game::singleton = NULL;

Game* Game::getInstance() {
    if(singleton == NULL) {
        Game();
    }

    return singleton;
}
Game::Game() {
    singleton = this;
    m_diff = 0;
    is_done = false;
}

Game::~Game() { 
    //delete m_map;
    //delete m_player;

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

    m_player = m_map->getPlayer();

    size_t last_ticks = SDL_GetTicks();

    while(!isDone()) {
        processEvent();

        // time update
        size_t ticks = SDL_GetTicks();
        m_diff = (ticks - last_ticks) / 1000.0;
        last_ticks = ticks;

        clear();

        m_map->update(m_diff);
        m_map->draw();

        updateScreen();
    }
}

void Game::clear() {
    SDL_FillRect(m_screen, NULL, 0x000000);
}

void Game::updateScreen() {
    SDL_Flip(m_screen);
}

void Game::processEvent() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            setDone(true);
            break;
        } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT) {
            m_player->setMove(LEFT);
        } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT) {
            m_player->setMove(RIGHT);
        } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) {
            m_player->setMove(UP);
        } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN) {
            m_player->setMove(DOWN);
        }
    }
}