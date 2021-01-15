#include "player.h"
#include <stdio.h>

void initPlayer(Player* playerPtr, Maze* mazePtr)
{
    playerPtr->position = preparePosition(0, 0);
    playerPtr->playerSign = 'P';
    playerPtr->mazePtr = mazePtr;
}

Position getMoveVector(int moveDirection)
{
    switch(moveDirection)
    {
        case MOVE_RIGHT: return preparePosition(1, 0); break;
        case MOVE_LEFT: return preparePosition(-1, 0); break; 
        case MOVE_TOP: return preparePosition(0, -1); break;
        case MOVE_DOWN: return preparePosition(0, 1); break;
    }

    return preparePosition(0, 0);
}

int checkIfCouldMove(int moveDirection, Player* player)
{
    Position moveVector = getMoveVector(moveDirection);
    Position newPosition = addPositions(player->position, moveVector);

    if(notWithinBounds(newPosition.x, player->mazePtr->width) || notWithinBounds(newPosition.y, player->mazePtr->height))
        return 0;

    switch(moveDirection)
    {
        case MOVE_RIGHT:
        {
            Cell currentCell = findCellByPosition(player->mazePtr, player->position);
            return !hasRightBorder(currentCell);
        }
        break;

        case MOVE_LEFT:
        { 
            Position leftNeighbor = preparePosition(player->position.x - 1, player->position.y);
            Cell leftCell = findCellByPosition(player->mazePtr, leftNeighbor);
            return !hasRightBorder(leftCell);
        }
        break;

        case MOVE_TOP:
        { 
            Position upNeighbor = preparePosition(player->position.x, player->position.y - 1);
            Cell upCell = findCellByPosition(player->mazePtr, upNeighbor);
            return !hasDownBorder(upCell);
        }
        break; 

        case MOVE_DOWN: 
        { 
            Cell currentCell = findCellByPosition(player->mazePtr, player->position);
            return !hasDownBorder(currentCell);
        }
        break;

        default:
            return 0;
    }
}

void movePlayer(int moveDirection, Player* player)
{
    Position moveVector = getMoveVector(moveDirection);
    player->position = addPositions(player->position, moveVector);
}