#include "snake.h"

void init_snake(snake **s)
{
	*s = malloc(sizeof(snake));
	(*s)->size = 1;
	lsnake *elt = malloc(sizeof(lsnake));
	elt->x = 0;
	elt->y = 0;
	elt->next = NULL;
	elt->prev = NULL;
	(*s)->head = elt;
	(*s)->last = elt;
	(*s)->surface = SDL_CreateRGBSurface(SDL_HWSURFACE, SNAKE_SIZE, SNAKE_SIZE, 32, 0, 0, 0, 0);
	SDL_FillRect((*s)->surface, NULL, SDL_MapRGB((*s)->surface->format, 17, 206, 112));
}

void delete_snake(snake *s)
{
	free(s->surface);
	lsnake *elt = s->head;
	while(elt != NULL){
		lsnake *tmp = elt;
		elt = elt->next;
		free(tmp->prev);
	}
	free(s);
}

void print_snake(SDL_Surface *screen, snake *s)
{
	SDL_Rect pos;
	lsnake *elt = s->head;
	while(elt != NULL){
		pos.x = SNAKE_SIZE * elt->x;
		pos.y = SNAKE_SIZE * elt->y;
		SDL_BlitSurface(s->surface, NULL, screen, &pos);
		elt = elt->next;
	}
}

int move_snake(snake* s, int dx, int dy, enum caseType map[SCREEN_W/SNAKE_SIZE][SCREEN_H/SNAKE_SIZE], bonus *b)
{
	lsnake *elt = malloc(sizeof(lsnake));
	elt->x = ((s->head->x + dx) + (SCREEN_W/SNAKE_SIZE)) % (SCREEN_W/SNAKE_SIZE);
	elt->y = ((s->head->y + dy) + (SCREEN_H/SNAKE_SIZE)) % (SCREEN_H/SNAKE_SIZE);
	elt->next = s->head;
	elt->prev = NULL;
	s->head->prev = elt;
	s->head = elt;
	s->size++;

	if(map[elt->x][elt->y]==SNAKE) return 1;
	
	if(map[elt->x][elt->y]==EMPTY) {
		lsnake* last = s->last;
		s->last = last->prev;
		last->prev->next = NULL;
		map[last->x][last->y] = EMPTY;
		free(last);
		s->size--;
	}
	map[elt->x][elt->y] = SNAKE;
	
	if(map[b->x][b->y] != APPLE) {
		b->x = rand()%((SCREEN_W/SNAKE_SIZE));
		b->y = rand()%((SCREEN_H/SNAKE_SIZE));
		if(map[b->x][b->y] == EMPTY)
			map[b->x][b->y] = APPLE;
	}

	return 0;
}
