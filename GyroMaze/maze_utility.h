#ifndef MAZE_UTILITY_H
#define MAZE_UTILITY_H

#include <stdio.h>
#include "maze.h"

void printPositions(Position* positions, int size);
void drawMaze(Maze* mazePtr);
void drawCell(Cell cell, Position cellPosition, int width, int height);
void printIndexes(int* possibleIndexes, int size);

#endif