/* GNONLONFOUN Sydney Schalom Eliel*/
#include "grid.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    Grid *grid = grid_create(4);
    assert(grid);

    assert(grid_get_size(grid) == 4);
    assert(grid_set_cell(grid, 1, 1, 42) == 0);
    assert(grid_get_cell(grid, 1, 1) == 42);

    Grid *clone = grid_clone(grid);
    assert(clone);
    assert(grid_get_cell(clone, 1, 1) == 42);

    grid_destroy(grid);
    grid_destroy(clone);

    printf("All grid tests passed.\n");
    return 0;
}

