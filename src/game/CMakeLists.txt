#/*GNONLONFOUN Sydney Schalom Eliel*/

add_library(game game.c)
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(game grid)

add_executable(test_game test_game.c)
target_link_libraries(test_game game)

