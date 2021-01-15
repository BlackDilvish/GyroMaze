#ifndef MAZE_UTILITY_H
#define MAZE_UTILITY_H

#include <stdio.h>
#include "maze.h"
#include "player.h"

int mazeIsSolved(Player* playerPtr);
void printPositions(Position* positions, int size);
void drawMaze(Maze* mazePtr, Player* playerPtr);
void drawCell(Cell cell, Position cellPosition, Position playerPosition, Position start, Position destination, int width, int height);
void printIndexes(int* possibleIndexes, int size);
void mazeToFile(Maze* mazePtr);

#endif