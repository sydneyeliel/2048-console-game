#/* GNONLONFOUN Sydney Schalom Eliel*/
add_library(grid grid.c)
target_include_directories(grid PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_grid test_grid.c)
target_link_libraries(test_grid grid)

