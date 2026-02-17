/* GNONLONFOUN Sydney Schalom Eliel*/
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    Game *game = game_create(4);
    srand((unsigned)time(NULL));

    while (!game_is_won(game) && !game_is_lost(game)) {
        MoveDirection dir = rand() % 4;
        game_move(game, dir);
    }

    if (game_is_won(game))
        printf("Random player won!\n");
    else
        printf("Random player lost.\n");

    printf("Final score: %d\n", game_get_score(game));

    game_save_score(game, "scores.txt");
    game_destroy(game);
    return 0;
}

