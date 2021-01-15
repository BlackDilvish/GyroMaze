#ifndef PLAYER_H
#define PLAYER_H

#include "maze.h"

#define MOVE_RIGHT 0
#define MOVE_LEFT 1
#define MOVE_TOP 2
#define MOVE_DOWN 3

typedef struct PlayerStruct {
    Position position;
    Maze* mazePtr;
    char playerSign;
} Player;

void initPlayer(Player* playerPtr, Maze* mazePtr);

Position getMoveVector(int moveDirection);
int checkIfCouldMove(int moveDirection, Player* player);
void movePlayer(int moveDirection, Player* player);

#endif