/* GNONLONFOUN Sydney Schalom Eliel*/

#include "game.h"
#include "game.inc"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* -------------------------------------------------- */
/* n x n safe                                         */
/* -------------------------------------------------- */
static void add_random_tile(Grid *grid)
{
    size_t size = grid_get_size(grid);
    size_t max = size * size;

    size_t (*empty)[2] = malloc(max * sizeof(*empty));
    if (!empty)
        return;

    size_t count = 0;

    for (size_t r = 0; r < size; r++) {
        for (size_t c = 0; c < size; c++) {
            if (grid_get_cell(grid, r, c) == 0) {
                empty[count][0] = r;
                empty[count][1] = c;
                count++;
            }
        }
    }

    if (count > 0) {
        size_t index = rand() % count;
        int value = (rand() % 10 == 0) ? 4 : 2;
        grid_set_cell(grid,
                      empty[index][0],
                      empty[index][1],
                      value);
    }

    free(empty);
}

/* -------------------------------------------------- */
/* Game creation / destruction                        */
/* -------------------------------------------------- */
Game *game_create(size_t size)
{
    Game *game = malloc(sizeof(Game));
    if (!game)
        return NULL;

    game->grid = grid_create(size);
    if (!game->grid) {
        free(game);
        return NULL;
    }

    game->score = 0;

    srand((unsigned)time(NULL));
    add_random_tile(game->grid);
    add_random_tile(game->grid);

    return game;
}

void game_destroy(Game *game)
{
    if (!game)
        return;

    grid_destroy(game->grid);
    free(game);
}

/* -------------------------------------------------- */
/* Slide and merge a single line (n x n safe)          */
/* -------------------------------------------------- */
static int slide_and_merge_line(int *line, size_t size, int *score)
{
    int moved = 0;

    int *merged = calloc(size, sizeof(int));
    if (!merged)
        return 0;

    for (size_t i = 0; i < size; i++) {
        if (line[i] == 0)
            continue;

        for (size_t j = i; j > 0; j--) {
            if (line[j - 1] == 0) {
                line[j - 1] = line[j];
                line[j] = 0;
                moved = 1;
            }
            else if (line[j - 1] == line[j] && !merged[j - 1]) {
                line[j - 1] *= 2;
                *score += line[j - 1];
                line[j] = 0;
                merged[j - 1] = 1;
                moved = 1;
                break;
            }
            else {
                break;
            }
        }
    }

    free(merged);
    return moved;
}

/* -------------------------------------------------- */
/* Perform a move                                     */
/* -------------------------------------------------- */
int game_move(Game *game, MoveDirection direction)
{
    if (!game || !game->grid)
        return 0;

    size_t size = grid_get_size(game->grid);
    int moved = 0;

    for (size_t i = 0; i < size; i++) {

        int *line = calloc(size, sizeof(int));
        if (!line)
            return 0;

        /* extract line */
        for (size_t j = 0; j < size; j++) {
            switch (direction) {
                case MOVE_LEFT:
                    line[j] = grid_get_cell(game->grid, i, j);
                    break;
                case MOVE_RIGHT:
                    line[j] = grid_get_cell(game->grid, i, size - 1 - j);
                    break;
                case MOVE_UP:
                    line[j] = grid_get_cell(game->grid, j, i);
                    break;
                case MOVE_DOWN:
                    line[j] = grid_get_cell(game->grid, size - 1 - j, i);
                    break;
            }
        }

        if (slide_and_merge_line(line, size, &game->score))
            moved = 1;

        /* write back */
        for (size_t j = 0; j < size; j++) {
            switch (direction) {
                case MOVE_LEFT:
                    grid_set_cell(game->grid, i, j, line[j]);
                    break;
                case MOVE_RIGHT:
                    grid_set_cell(game->grid, i, size - 1 - j, line[j]);
                    break;
                case MOVE_UP:
                    grid_set_cell(game->grid, j, i, line[j]);
                    break;
                case MOVE_DOWN:
                    grid_set_cell(game->grid, size - 1 - j, i, line[j]);
                    break;
            }
        }

        free(line);
    }

    if (moved)
        add_random_tile(game->grid);

    return moved;
}

/* -------------------------------------------------- */
/* Game state checks                                  */
/* -------------------------------------------------- */
int game_can_move(const Game *game)
{
    size_t size = grid_get_size(game->grid);

    for (size_t r = 0; r < size; r++) {
        for (size_t c = 0; c < size; c++) {
            int value = grid_get_cell(game->grid, r, c);
            if (value == 0)
                return 1;
            if (c + 1 < size && value == grid_get_cell(game->grid, r, c + 1))
                return 1;
            if (r + 1 < size && value == grid_get_cell(game->grid, r + 1, c))
                return 1;
        }
    }
    return 0;
}

int game_is_won(const Game *game)
{
    size_t size = grid_get_size(game->grid);

    for (size_t r = 0; r < size; r++)
        for (size_t c = 0; c < size; c++)
            if (grid_get_cell(game->grid, r, c) == 2048)
                return 1;

    return 0;
}

int game_is_lost(const Game *game)
{
    return !game_can_move(game);
}

/* -------------------------------------------------- */
/* Accessors                                          */
/* -------------------------------------------------- */
const Grid *game_get_grid(const Game *game)
{
    return game->grid;
}

int game_get_score(const Game *game)
{
    return game->score;
}

/* -------------------------------------------------- */
/* Score saving                                       */
/* -------------------------------------------------- */
int game_save_score(const Game *game, const char *filename)
{
    FILE *file = fopen(filename, "a");
    if (!file)
        return -1;

    fprintf(file, "%d\n", game->score);
    fclose(file);
    return 0;
}

/* -------------------------------------------------- */
/* Save / Load full game                              */
/* -------------------------------------------------- */
int game_save(const Game *game, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
        return -1;

    size_t size = grid_get_size(game->grid);
    fprintf(file, "%zu %d\n", size, game->score);

    for (size_t r = 0; r < size; r++) {
        for (size_t c = 0; c < size; c++) {
            fprintf(file, "%d ", grid_get_cell(game->grid, r, c));
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 0;
}

Game *game_load(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
        return NULL;

    size_t size;
    int score;

    if (fscanf(file, "%zu %d", &size, &score) != 2) {
        fclose(file);
        return NULL;
    }

    Game *game = malloc(sizeof(Game));
    if (!game) {
        fclose(file);
        return NULL;
    }

    game->grid = grid_create(size);
    if (!game->grid) {
        free(game);
        fclose(file);
        return NULL;
    }

    game->score = score;

    for (size_t r = 0; r < size; r++) {
        for (size_t c = 0; c < size; c++) {
            int value;
            fscanf(file, "%d", &value);
            grid_set_cell(game->grid, r, c, value);
        }
    }

    fclose(file);
    return game;
}

