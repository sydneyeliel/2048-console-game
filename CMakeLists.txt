#/* GNONLONFOUN Sydney Schalom Eliel*/
cmake_minimum_required(VERSION 3.10)
project(2048 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

add_subdirectory(src/grid)
add_subdirectory(src/game)
add_subdirectory(src/programs)

