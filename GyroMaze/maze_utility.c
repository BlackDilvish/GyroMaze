#include "maze_utility.h"
#include <stdio.h>

//tutaj troche pomocniczych funkcji do debuggowania tego spaghetii oraz do narysowania sobie czegoś labiryntopodobnego,
//ze wzgledu na moja nieumiejetnosc ustalenia szerokosci znakow w konsoli, czasami labirynt wyglada dziwnie + na odwrot szerokosc/wysokosc, 
//ale chyba z grubsza
//jest ok

int mazeIsSolved(Player* playerPtr)
{
    return (positionsCompare(playerPtr->position, playerPtr->mazePtr->destination) == 0);
}

void printPositions(Position* positions, int size)
{
    for(int i = 0; i < size; ++i)
    {
        printf("%d. (%d, %d)\n", i + 1, positions[i].x, positions[i].y);
    }
}

void drawMaze(Maze* mazePtr, Player* playerPtr)
{
    printf(" ");
    for(int i = 0; i < mazePtr->width; ++i)
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
            drawCell(mazePtr->cells[currentIndex], currentPosition, playerPtr->position, 
            mazePtr->start, mazePtr->destination, mazePtr->width, mazePtr->height);
        }

        printf("\n");
    }
}

void drawCell(Cell cell, Position cellPosition, Position playerPosition, Position start, Position destination, int width, int height)
{
    /*else if(cellPosition.y == height - 1)
    {
        printf("_");
    }*/

    if(positionsCompare(cellPosition, playerPosition) == 0)
    {
        //switch(cell.walls)
        {
            printf("P");
            /*case 0: printf("P"); break;
            case 1: printf("P"); break;
            case 2: printf("P"); break;
            case 3: printf("P"); break;*/
        }
    }

    else if(positionsCompare(cellPosition, start) == 0)
    {
        switch(cell.walls)
        {
            case 0: printf("@"); break;
            case 1: printf("@"); break;
            case 2: printf("@"); break;
            case 3: printf("@"); break;
        }
    }

    else if(positionsCompare(cellPosition, destination) == 0)
    {
        printf("X");
        /*switch(cell.walls)
        {
            case 0: printf("  X  "); break;
            case 1: printf("  X |"); break;
            case 2: printf("__X__"); break;
            case 3: printf("__X_|"); break;
        }*/
    }

    else printf("%d", cell.walls); /*switch(cell.walls)
    {
        case 0: printf("     "); break;
        case 1: printf("    |"); break;
        case 2: printf("_____"); break;
        case 3: printf("____|"); break;
    }*/

    if(cellPosition.x == width - 1)
    {
        printf("|");
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

void mazeToFile(Maze* mazePtr)
{
    FILE* file = fopen("mazeFile.dat", "w");

    for(int i = 0; i < mazePtr->width * mazePtr->height; ++i)
    {
        fprintf(file, "%d\n", mazePtr->cells[i].walls);
    }

    fclose(file);
}
