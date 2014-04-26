#ifndef DEF_SNAKE
#define DEF_SNAKE

#include <assert.h>
#include <SDL/SDL.h>
#include "const.h"

typedef struct bonus bonus;
struct bonus{
	int x, y;
};

typedef struct lsnake lsnake;
struct lsnake{
	int x, y;
	lsnake *next;
	lsnake *prev;
};

typedef struct snake snake;
struct snake{
	int size;
	SDL_Surface *surface;
	lsnake *head;
	lsnake *last;
};

void init_snake(snake**);
void print_snake(SDL_Surface*, snake*);
void delete_snake(snake*);

int move_snake(snake*, int, int, enum caseType[SCREEN_W/SNAKE_SIZE][SCREEN_H/SNAKE_SIZE], bonus*);
#endif