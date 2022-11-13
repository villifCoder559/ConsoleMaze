cmake_minimum_required(VERSION 3.0.0)
project(MazeSolver VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

add_executable(MazeSolver main.cpp Move.h Move.cpp Node.h Node.cpp Maze.h Maze.cpp)

