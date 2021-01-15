#ifndef MAZE_GRAPHIC_H
#define MAZE_GRAPHIC_H

#include "maze.h"
#include "player.h"
#include "graphics.h"

void drawMaze(Maze* mazePtr, int screenWidth, int screenHeight);
void drawPlayer(Player* playerPtr, int screenWidth, int screenHeight);

#endif