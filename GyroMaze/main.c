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

int RTCounter = 0;
void RTC_IRQHandler()
{
	LPC_RTC->ILR = 1;
	RTCounter++;
}

int main()
{
	Joystick_Initialize();
	initUart();
	initGraphics();
	fillWindow(LCDWhite);
	I2CInit();
	initGyro();
	
	//init RTC
	LPC_RTC->CCR = 1;
	LPC_RTC->ILR = 1;
	LPC_RTC->CIIR = 1;
	NVIC_EnableIRQ(RTC_IRQn); //co sekunde
	
	writeString("asdasdsadasd");
	
	drawMainMenu();
	
    int selected_width = 12;
    int selected_height = 16;

		writeString("przed inicjalizacja");
	
    int cellsSize = width * height;
		
		writeString("po inizjalizacji statycznej pamieci");


    fillCells(cells, cellsSize);
    initPositions(positions, selected_width, selected_height);
		
		writeString("po operacjach na komorkach i pozycjach");

    Stack* stackPtr = &stack;
    Maze* mazePtr = &maze; 
    Player* playerPtr = &player;

		writeString("wskazniki do pamieci");

    initStack(stackPtr, stackPositions, cellsSize);
    initMaze(mazePtr, cells, visitedPositions, positions, stackPtr, selected_width, selected_height);
    initPlayer(playerPtr, mazePtr);
		
		writeString("inicjalizacja stosu, mazea itp.");


    generateMaze(mazePtr);

    //tutaj narysowac tam gdzie sa polaczenia albo na odwrot
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
			RTCounter = 0;
				if(isMazeSolved(playerPtr)
				{
					appState = MAIN_MENU_STATE; //przenosimy do main menu
					drawMainMenu();
					/*if(RTCounter < LPC_RTC->GPREG0) //oby to było tak proste
					{
						//nowy najlepszy czas
						LPC_RTC->GPREG0 = RTCounter;
					}*/
				}
				drawMaze(mazePtr, 240, 320);
				drawPlayer(playerPtr, 240, 320);
			
				switch(Joystick_GetState()) //tutaj pewnie zmienimy na sterowanie żyroskopem
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
			
			case LEADERBOARD_STATE:
			updateLeaderboard();
			printf("LEADERBOARD_STATE\n");
			break;

			default:
			break;
		}
					

		for(int i=0; i<10000000; i++); //fancy delay
	}
}
