/* GNONLONFOUN Sydney Schalom Eliel */

#include "game.h"
#include "grid.h"

#include <stdio.h>
#include <stdlib.h>

/* ANSI colors */
#define ANSI_RESET     "\033[0m"
#define ANSI_BLACK_BG  "\033[40m"
#define ANSI_WHITE     "\033[97m"

/* -------------------------------------------------- */
/* Print horizontal separator (white on black)        */
/* -------------------------------------------------- */
static void print_separator(size_t size)
{
    for (size_t i = 0; i < size; i++) {
        printf("+------");
    }
    printf("+\n");
}

/* -------------------------------------------------- */
/* Display game with black background and white grid  */
/* -------------------------------------------------- */
static void display_game(const Game *game)
{
    const Grid *grid = game_get_grid(game);
    size_t size = grid_get_size(grid);

    system("clear");

    /* persistent black background + white text */
    printf(ANSI_BLACK_BG ANSI_WHITE);

    /* top border */
    print_separator(size);

    for (size_t r = 0; r < size; r++) {

        /* cell values */
        for (size_t c = 0; c < size; c++) {
            int value = grid_get_cell(grid, r, c);

            if (value == 0)
                printf("|      ");
            else
                printf("| %4d ", value);
        }
        printf("|\n");

        /* separator */
        print_separator(size);
    }

    /* reset colors */
    printf(ANSI_RESET);
    printf("\nScore: %d\n", game_get_score(game));
}

/* -------------------------------------------------- */
/* Main program                                       */
/* -------------------------------------------------- */
int main(int argc, char *argv[])
{
    int size = 4;

    if (argc == 2) {
        size = atoi(argv[1]);
        if (size < 2)
            size = 4;
    }

    Game *game = game_create(size);
    char input;

    while (1) {
        display_game(game);

        if (game_is_won(game)) {
            printf("You won!\n");
            break;
        }

        if (game_is_lost(game)) {
            printf("Game over!\n");
            break;
        }

        printf("Move (w/a/s/d, n=new, S=save, l=load, q=quit): ");
        scanf(" %c", &input);

        switch (input) {
            case 'w': game_move(game, MOVE_UP);    break;
            case 's': game_move(game, MOVE_DOWN);  break;
            case 'a': game_move(game, MOVE_LEFT);  break;
            case 'd': game_move(game, MOVE_RIGHT); break;

            case 'n':
                game_destroy(game);
                game = game_create(size);
                break;

            case 'S':
                game_save_score(game, "scores.txt");
                break;

            case 'l': {
                Game *loaded = game_load("save.txt");
                if (loaded) {
                    game_destroy(game);
                    game = loaded;
                }
                break;
            }

            case 'q':
                goto end;

            default:
                break;
        }
    }

end:
    game_save_score(game, "scores.txt");
    game_destroy(game);
    return 0;
}

