/* GNONLONFOUN Sydney Schalom Eliel*/
#ifndef GAME_H
#define GAME_H

#include "grid.h"
#include <stddef.h>

typedef struct _Game Game;

typedef enum {
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT
} MoveDirection;

/* Constructors / destructors */
Game *game_create(size_t size);
void game_destroy(Game *game);

/* Gameplay */
int game_move(Game *game, MoveDirection direction);
int game_can_move(const Game *game);
int game_is_won(const Game *game);
int game_is_lost(const Game *game);

/* Accessors */
const Grid *game_get_grid(const Game *game);
int game_get_score(const Game *game);

/* Persistence */
int game_save(const Game *game, const char *filename);
Game *game_load(const char *filename);
int game_save_score(const Game *game, const char *filename);

#endif

