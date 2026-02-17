/* GNONLONFOUN Sydney Schalom Eliel*/
#include "game.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    Game *game = game_create(4);
    assert(game);

    assert(game_get_score(game) == 0);
    assert(game_can_move(game));

    game_move(game, MOVE_LEFT);
    game_move(game, MOVE_RIGHT);
    game_move(game, MOVE_UP);
    game_move(game, MOVE_DOWN);

    printf("Game logic tests passed.\n");

    game_destroy(game);
    return 0;
}

