#include "mazeGraphic.h"

void drawMaze(Maze* mazePtr, int screenWidth, int screenHeight)
{
    int currentWidth = 0;
    int currentHeight = 0;
	
		fillWindow(LCDBlack);

    int moveWidth = screenWidth / mazePtr->width; //chyba musi byc int
    int moveHeight = screenHeight / mazePtr->height; //chyba musi byc int

    for(int j = 0; j < mazePtr->height; ++j)
    {
        for(int i = 0; i < mazePtr->width; ++i)
        {
            Position position = preparePosition(i, j);
            int index = getIndexFromPosition(position, mazePtr->width, mazePtr->height);

            currentWidth = i * moveWidth;
            currentHeight = j * moveHeight;

            int wallNumber = mazePtr->cells[index].walls;

            if(index == getIndexFromPosition(mazePtr->destination, mazePtr->width, mazePtr->height))
            {
                drawRectangle(currentWidth + 1, currentHeight + 1, moveWidth - 1, moveHeight - 1, LCDRed); //rysujemy mete
            }

            switch(wallNumber)
            {
                case 1: drawLine(currentWidth + moveWidth, currentHeight, currentWidth + moveWidth, currentHeight + moveHeight, LCDWhite); 
                break;
                case 2: drawLine(currentWidth, currentHeight + moveHeight, currentWidth + moveWidth, currentHeight + moveHeight, LCDWhite); 
                break;
                case 3: 
                    drawLine(currentWidth + moveWidth, currentHeight, currentWidth + moveWidth, currentHeight + moveHeight, LCDWhite);
                    drawLine(currentWidth, currentHeight + moveHeight, currentWidth + moveWidth, currentHeight + moveHeight, LCDWhite);
                break;
            }
        }
    }
}

void drawPlayer(Player* playerPtr, int screenWidth, int screenHeight)
{
    int moveWidth = screenWidth / playerPtr->mazePtr->width;
    int moveHeight = screenHeight / playerPtr->mazePtr->height;
    int x = playerPtr->position.x * moveWidth;
    int y = playerPtr->position.y * moveHeight;

    drawRectangle(x, y, moveWidth - 1, moveHeight - 1, LCDGreen);
}