#include <stdlib.h>
#include <SDL.h>
#include "Config.h"
#include "Map.h"
#include "Game.h"

SDL_Surface *pacman = NULL;
SDL_Surface *screen = NULL;
int px = 30*15, py = 30*17;
int dir = 0;

int main(int argc, char* argv[])
{
    SDL_Rect rSprite;
    SDL_Rect rect;

    rSprite.h = 33;
    rSprite.w = 33;

    rect.h = 33;
    rect.w = 33;

    Game *game = Game::getInstance();
    game->run();

    pacman = SDL_LoadBMP("images/pacman.bmp");

    if(pacman == NULL)
        printf("pacman error \n");
    bool is_done = false;

    /*while(!is_done) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_done = true;
                break;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT) {
                dir = 0;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT) {
                dir = 1;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) {
                dir = 2;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN) {
                dir = 3;
            }
        }

        switch(dir) {
        case 0:
            if(map[py/30][(px-30)/30] != 'X') 
                px -= 30;
            else dir = 4;
            break;
        case 1:
            if(map[py/30][(px+30)/30] != 'X') 
                px += 30;
            else dir = 4;
            break;
        case 2:
            if(map[(py-30)/30][px/30] != 'X') 
                py -= 30;
            else dir = 4;
            break;
        case 3:
            if(map[(py+30)/30][px/30] != 'X') 
                py += 30;
            else dir = 4;
            break;
        }
        
        if(px == Config::WIN_W) {
            px = 0;
        } 
        if(px == -30) {
            px = Config::WIN_W;
        }
        rect.x = px;
        rect.y = py;

        rSprite.x = dir*33;
        rSprite.y = 0;

        
        SDL_FillRect(screen,NULL, 0x000000); 

        int colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
        SDL_SetColorKey(pacman, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
        
        mapa->draw();
        SDL_BlitSurface(pacman, &rSprite, screen, &rect);
        SDL_Flip(screen);
        SDL_Delay(70);
        
        rSprite.x = 33*4;
        SDL_BlitSurface(pacman, &rSprite, screen, &rect);
        SDL_Flip(screen);
        SDL_Delay(70);
    }
    */
    SDL_FreeSurface(pacman);

    return 0;
}
