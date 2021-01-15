#include "LPC17xx.h"                    // Device header
#include "PIN_LPC17xx.h"
#include "Board_Joystick.h"
#include <stdio.h>
#include "graphics.h"
#include "maze.h"
#include "player.h"
#include "i2c.h"
#include "uart.h"
#include "gyro.h"
#include "menu.h"
#include "mazeGraphic.h"
#include "Board_Buttons.h"

#define width 30
#define height 30

Stack stack;
Maze maze;
Cell cells[width * height];
Player player;
Position positions[width * height]; 
Position stackPositions[width * height];//ta tablica bedzie dzialac jak stos do zapamietywania ostatnio odwiedzonych pozycji
Position visitedPositions[width * height];

int main()
{
	Joystick_Initialize();
	initUart();
	initGraphics();
	fillWindow(LCDWhite);
	I2CInit();
	initGyro();
	
	writeString("asdasdsadasd");
	
	drawMainMenu();
	
	    //to tylko dla testowania w konsoli
    int selected_width = 12;
    int selected_height = 16;
    //to tylko dla testowania w konsoli

		writeString("przed inicjalizacja");
	
    int cellsSize = width * height;
		
		writeString("po inizjalizacji statycznej pamieci");


    clearCells(cells, cellsSize);
    initPositions(positions, selected_width, selected_height);
		
		writeString("po operacjach na komorkach i pozycjach");

    //wskazniki do statycznie alokowanej pamieci
    Stack* stackPtr = &stack;
    Maze* mazePtr = &maze; 
    Player* playerPtr = &player;

		writeString("wskazniki do pamieci");

    initStack(stackPtr, stackPositions, cellsSize);
    initMaze(mazePtr, cells, visitedPositions, positions, stackPtr, selected_width, selected_height);
    initPlayer(playerPtr, mazePtr);
		
		writeString("inicjalizacja stosu, mazea itp.");


    generateMaze(mazePtr);

    //tutaj narysowac tam gdzie sa polaczenia albo na odwrót
    //drawMaze(mazePtr, playerPtr);

	while(true)
	{
		switch(appState)
		{
			case MAIN_MENU_STATE:
			updateMainMenu();
			writeString("MAIN_MENU_STATE");
			break;

			case SELECT_SIZE_STATE:
			updateSelectSize();
			writeString("SELECT_SIZE_STATE");
			break;

			case GAME_STATE:
				drawMaze(mazePtr, 240, 320);
				drawPlayer(playerPtr, 240, 320);
			
				switch(Joystick_GetState())
				{
					case JOYSTICK_UP:
						if(checkIfCouldMove(MOVE_TOP, playerPtr))
					movePlayer(MOVE_TOP, playerPtr);
					writeString("JOYSTICK_UP");
					BUTTON_DELAY;
					break;
					
					case JOYSTICK_DOWN:
						if(checkIfCouldMove(MOVE_DOWN, playerPtr))
					movePlayer(MOVE_DOWN, playerPtr);
					writeString("JOYSTICK_DOWN");
					BUTTON_DELAY;
					break;
					
					case JOYSTICK_LEFT:
					if(checkIfCouldMove(MOVE_LEFT, playerPtr))
						movePlayer(MOVE_LEFT, playerPtr);
					writeString("JOYSTICK_LEFT");
					BUTTON_DELAY;
					break;
					
					case JOYSTICK_RIGHT:
						if(checkIfCouldMove(MOVE_RIGHT, playerPtr))
						movePlayer(MOVE_RIGHT, playerPtr);
						writeString("JOYSTICK_RIGHT");
					BUTTON_DELAY;
					break;
				}
			{
				
			Coordinates coords;
			getData(&coords);

			char buffer[50];
			sprintf(buffer, "x: %d, y: %d, z: %d", coords.x, coords.y, coords.z);
			writeString(buffer);
			}
			
			break;

			default:
			break;
		}
					

		for(int i=0; i<10000000; i++); //fancy delay
	}
}
