#include "maze_utility.h"
#include <stdio.h>

//tutaj troche pomocniczych funkcji do debuggowania tego spaghetii oraz do narysowania sobie czegoś labiryntopodobnego,
//ze wzgledu na moja nieumiejetnosc ustalenia szerokosci znakow w konsoli, czasami labirynt wyglada dziwnie + na odwrot szerokosc/wysokosc, 
//ale chyba z grubsza
//jest ok

void printPositions(Position* positions, int size)
{
    for(int i = 0; i < size; ++i)
    {
        printf("%d. (%d, %d)\n", i + 1, positions[i].x, positions[i].y);
    }
}

void drawMaze(Maze* mazePtr)
{
    printf(" ");
    for(int i = 0; i < mazePtr->height; ++i)
    {
        printf("_ ");
    }

    printf("\n");

    for(int i = 0; i < mazePtr->height; ++i)
    {
        printf("|");

        for(int j = 0; j < mazePtr->width; ++j)
        {
            Position currentPosition = preparePosition(j, i);
            int currentIndex = getIndexFromPosition(currentPosition, mazePtr->width, mazePtr->height);
            drawCell(mazePtr->cells[currentIndex], currentPosition, mazePtr->width, mazePtr->height);
        }

        printf("\n");
    }
}

void drawCell(Cell cell, Position cellPosition, int width, int height)
{
    if(cellPosition.x == width - 1)
    {
        printf("|");
    }

    else if(cellPosition.y == height - 1)
    {
        printf("_ ");
    }

    else switch(cell.walls)
    {
        case 0: printf("  "); break;
        case 1: printf(" |"); break;
        case 2: printf("_ "); break;
        case 3: printf("_|"); break;
    }
}

void printIndexes(int* possibleIndexes, int size)
{
    for(int i = 0; i < size; ++i)
    {
        printf("possibleIndexes[%d] = %d,", i, possibleIndexes[i]);
    }

    printf("\n");
}