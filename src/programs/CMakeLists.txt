#/* GNONLONFOUN Sydney Schalom Eliel*/
add_executable(2048-play 2048-play.c)
target_link_libraries(2048-play game)

add_executable(2048-random 2048-random.c)
target_link_libraries(2048-random game)
add_executable(2048-display-scores 2048-display-scores.c)

