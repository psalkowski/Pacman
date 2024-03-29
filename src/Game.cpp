#include "Game.h"

Game::Game() {

    m_diff = 0;
    is_done = false;

    m_screen = NULL;
    m_map = NULL;
    m_player = NULL;
    m_text = NULL;
}

Game::~Game() { 
    delete m_map;
    delete m_player;

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
    TTF_Init();
}

void Game::run() {
    initGraph();
    
    m_map = new Map(m_screen);
    m_map->convertFileToMap("level/level-1.txt");

    m_player = m_map->getPlayer();

    size_t last_ticks = SDL_GetTicks();

    SDL_Color text_color = {100, 100, 100};

    TTF_Font *font = NULL;
    font = TTF_OpenFont("font/FreeSansBold.ttf", 24);

    if(font == NULL) {
        cout << "error " << endl;
        cerr << TTF_GetError() << endl;
        return; 
    }

    while(!isDone()) {
        
        processEvent();

        if(m_player->getLife() > 0) {
            // time update
            size_t ticks = SDL_GetTicks();
            m_diff = (ticks - last_ticks) / 1000.0;
            last_ticks = ticks;

            clear();

            m_map->update(m_diff);
            m_map->draw();

            m_text = TTF_RenderText_Solid(font, m_player->getStatistic().c_str(), text_color);
            cout << m_player->getStatistic() << endl;

            SDL_BlitSurface(m_text, NULL, m_screen, NULL);
            updateScreen();
        }
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
