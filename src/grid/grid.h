/* GNONLONFOUN Sydney Schalom Eliel*/
#ifndef GRID_H
#define GRID_H

#include <stddef.h>

typedef struct _Grid Grid;

/* Constructors / destructors */
Grid *grid_create(size_t size);
Grid *grid_clone(const Grid *grid);
void grid_destroy(Grid *grid);

/* Accessors */
size_t grid_get_size(const Grid *grid);
int grid_get_cell(const Grid *grid, size_t row, size_t col);

/* Modifiers */
int grid_set_cell(Grid *grid, size_t row, size_t col, int value);

/* I/O */
int grid_save_to_file(const Grid *grid, const char *filename);
Grid *grid_load_from_file(const char *filename);

/* Display */
int grid_to_string(const Grid *grid, char *buffer, size_t buffer_size);

#endif

