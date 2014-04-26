#include <stdlib.h>
#include <SDL/SDL.h>
#include <assert.h>

#include "const.h"
#include "snake.h"

int main(int argc, char *argv[])
{
	SDL_Surface *screen = NULL, *bonusSurf = NULL;
    int prevTime = 0;
	bonusSurf = SDL_CreateRGBSurface(SDL_HWSURFACE, SNAKE_SIZE, SNAKE_SIZE, 32, 0, 0, 0, 0);
	SDL_FillRect(bonusSurf, NULL, SDL_MapRGB(bonusSurf->format, 206, 17, 112));

	bonus b;
    b.x = 2;
    b.y = 2;

	SDL_Event event;

	snake *s = NULL;
	init_snake(&s);

	enum caseType map[SCREEN_W/SNAKE_SIZE][SCREEN_H/SNAKE_SIZE];
	for(int i=0;i<SCREEN_W/SNAKE_SIZE;++i)
		for(int j=0;j<SCREEN_H/SNAKE_SIZE;++j)
			map[i][j] = EMPTY;

     map[b.x][b.y] = APPLE;   

	enum dir dir = RIGHT;

    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Da Snake !", NULL);

    int exit_game = 0;
    while (!exit_game) {
        SDL_PollEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                exit_game = 1;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        if(dir != DOWN)
                        	dir = UP;
                        break;
                    case SDLK_RIGHT:
                        if(dir != LEFT)
                        	dir = RIGHT;
                        break;
                    case SDLK_DOWN:
                        if(dir != UP)
                        	dir = DOWN;
                        break;
                    case SDLK_LEFT:
                        if(dir != RIGHT)
                        	dir = LEFT;
                        break;
                    default:
		            	break;
                }
                break;
        }

        switch(dir) {
        	case UP:
        		exit_game |= move_snake(s, 0, -1, map, &b);
        		break;
        	case RIGHT:
        		exit_game |= move_snake(s, 1, 0, map, &b);
        		break;
        	case DOWN:
        		exit_game |= move_snake(s, 0, 1, map, &b);
        		break;
        	default:
        		exit_game |= move_snake(s, -1, 0, map, &b);
        		break;
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
        
        if(map[b.x][b.y]==APPLE) {
            SDL_Rect posBonus;
            posBonus.x = SNAKE_SIZE * b.x;
            posBonus.y = SNAKE_SIZE * b.y;
            SDL_BlitSurface(bonusSurf, NULL, screen, &posBonus);
		}
        print_snake(screen, s);
        SDL_Flip(screen);
    

        int currTime = SDL_GetTicks();
        if (currTime - prevTime < DELAY)
           SDL_Delay(DELAY + prevTime - currTime);
        prevTime = currTime;
    }

    delete_snake(s);
    free(bonusSurf);
    SDL_Quit();

    return EXIT_SUCCESS;
}
