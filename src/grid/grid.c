/* GNONLONFOUN Sydney Schalom Eliel */

#include "grid.h"
#include "grid.inc"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Create a new empty grid of size n x n.
 * All cells are initialized to 0.
 */
Grid *grid_create(size_t size)
{
    Grid *grid = malloc(sizeof(Grid));
    if (!grid)
        return NULL;

    grid->size = size;

    /* Allocate memory for all cells */
    grid->cells = calloc(size * size, sizeof(int));
    if (!grid->cells) {
        free(grid);
        return NULL;
    }

    return grid;
}

/*
 * Create a deep copy of an existing grid.
 */
Grid *grid_clone(const Grid *grid)
{
    if (!grid)
        return NULL;

    Grid *clone = grid_create(grid->size);
    if (!clone)
        return NULL;

    /* Copy cell values */
    memcpy(clone->cells,
           grid->cells,
           grid->size * grid->size * sizeof(int));

    return clone;
}

/*
 * Free all memory associated with a grid.
 */
void grid_destroy(Grid *grid)
{
    if (!grid)
        return;

    free(grid->cells);
    free(grid);
}

/*
 * Get the size of the grid.
 */
size_t grid_get_size(const Grid *grid)
{
    return grid ? grid->size : 0;
}

/*
 * Get the value stored in a cell.
 * Returns 0 if the position is invalid.
 */
int grid_get_cell(const Grid *grid, size_t row, size_t col)
{
    if (!grid || row >= grid->size || col >= grid->size)
        return 0;

    return grid->cells[row * grid->size + col];
}

/*
 * Set the value of a cell.
 * Returns 0 on success, -1 on error.
 */
int grid_set_cell(Grid *grid, size_t row, size_t col, int value)
{
    if (!grid || row >= grid->size || col >= grid->size)
        return -1;

    grid->cells[row * grid->size + col] = value;
    return 0;
}

/*
 * Save the grid to a text file.
 * The file format is:
 *  - grid size on the first line
 *  - all cell values on the second line
 */
int grid_save_to_file(const Grid *grid, const char *filename)
{
    if (!grid || !filename)
        return -1;

    FILE *file = fopen(filename, "w");
    if (!file)
        return -1;

    fprintf(file, "%zu\n", grid->size);

    for (size_t i = 0; i < grid->size * grid->size; i++) {
        fprintf(file, "%d ", grid->cells[i]);
    }

    fclose(file);
    return 0;
}

/*
 * Load a grid from a text file.
 * The file must follow the format used by grid_save_to_file.
 */
Grid *grid_load_from_file(const char *filename)
{
    if (!filename)
        return NULL;

    FILE *file = fopen(filename, "r");
    if (!file)
        return NULL;

    size_t size;
    fscanf(file, "%zu", &size);

    Grid *grid = grid_create(size);
    if (!grid) {
        fclose(file);
        return NULL;
    }

    for (size_t i = 0; i < size * size; i++) {
        fscanf(file, "%d", &grid->cells[i]);
    }

    fclose(file);
    return grid;
}

/*
 * Write a textual representation of the grid into a buffer.
 * This function is safe against buffer overflows.
 */
int grid_to_string(const Grid *grid, char *buffer, size_t buffer_size)
{
    if (!grid || !buffer || buffer_size == 0)
        return -1;

    size_t offset = 0;
    int written = 0;

    for (size_t r = 0; r < grid->size; r++) {
        for (size_t c = 0; c < grid->size; c++) {

            /* Write each cell value */
            written = snprintf(buffer + offset,
                               buffer_size - offset,
                               "%4d ",
                               grid_get_cell(grid, r, c));

            /* Check for buffer overflow */
            if (written < 0 || (size_t)written >= buffer_size - offset)
                return -1;

            offset += (size_t)written;
        }

        /* New line at the end of each row */
        written = snprintf(buffer + offset,
                           buffer_size - offset,
                           "\n");

        if (written < 0 || (size_t)written >= buffer_size - offset)
            return -1;

        offset += (size_t)written;
    }

    return 0;
}

