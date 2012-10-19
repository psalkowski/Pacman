#include "primlib\primlib.h"
#include <stdlib.h>

#include "Config.h"
//#include "Player.h"

SDL_Surface *buffer;
SDL_Surface *mapa = NULL;
SDL_Surface *pacman = NULL;

int px = 30*15, py = 30*17;
int dir = 0;

char map[Config::MAP_ROW][Config::MAP_COL]={ 
  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
  "X  o |o o o XXXXX o o o| o  X",
  "X XXX XXXXX XXXXX XXXXX XXX X",
  "XoXXX XXXXX XXXXX XXXXX XXXoX",
  "X      o|o   o o   o|o      X",
  "XoXXXoXX XXXXXXXXXXX XXoXXXoX",
  "X    |XX    |XXX|    XX     X",
  "XoXXXoXXXXXX XXX XXXXXXoXXXoX",
  "X XXXoXX ooo|ooo|ooo XXoXXX X",
  " o   |XX XXXXXXXXXXX XX|   o ",
  "X XXXoXX XXXXXXXXXXX XXoXXX X",
  "XoXXXoXX oo |ooo|ooo XXoXXXoX",
  "X XXXoXXXXXX XXX XXXXXXoXXX X",
  "X     XX     XXX     XX     X",
  "X XXXoXX XXXXXXXXXXX XXoXXX X",
  "XoXXX| o| o o o o o |o |XXXoX",
  "X XXXoXXXX XXXXXXXX XXX XXX X",
  "XoXXXoXXXX          XXX XXXoX",
  "X  o |o o  XXXXXXXX o o| o  X",
  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};

void initGraphic() {
	/* Initialize SDL */
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
		return;
	}
	buffer = SDL_SetVideoMode(Config::WIN_W,Config::WIN_H,32,SDL_SWSURFACE | SDL_DOUBLEBUF);
}

void drawMap() {
	for(int row = 0; row < Config::MAP_ROW; row++) {
		for(int col = 0; col < Config::MAP_COL; col++) {
			if(map[row][col] == 'X') {
				SDL_Rect  destR;
				destR.x = col*30;
				destR.y = row*30;

				SDL_BlitSurface(mapa, NULL, buffer, &destR);

			}
		}
	}
}

double timer = 0.3;
void update(double dt) {
	if(timer > dt) { }

}
int main(int argc, char* argv[])
{
	SDL_Rect rSprite;
	SDL_Rect rect;

	rSprite.h = 33;
	rSprite.w = 33;

	rect.h = 33;
	rect.w = 33;

	bool is_done = false;

	initGraphic();

	double v = 0.1;
	size_t last_ticks = SDL_GetTicks();
	mapa = SDL_LoadBMP("images/roca.bmp");
	pacman = SDL_LoadBMP("images/pacman.bmp");

	if(pacman == NULL)
		printf("pacman error \n");

	if(mapa == NULL)
		printf("mapa error \n");

	while(!is_done) {

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

		// time update
		size_t ticks = SDL_GetTicks();
		double delta_time = (ticks - last_ticks) / 1000.0;
		last_ticks = ticks;

		
		SDL_FillRect(buffer,NULL, 0x000000); 

		int colorkey = SDL_MapRGB(buffer->format, 255, 0, 255);
		SDL_SetColorKey(pacman, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		
		drawMap();
		SDL_BlitSurface(pacman, &rSprite, buffer, &rect);
		SDL_Flip(buffer);
		SDL_Delay(70);
		
		rSprite.x = 33*4;
		SDL_BlitSurface(pacman, &rSprite, buffer, &rect);
		SDL_Flip(buffer);
		SDL_Delay(70);
	}
	
	SDL_FreeSurface(pacman);
	SDL_FreeSurface(buffer);

	SDL_Quit();

	return 0;
}
