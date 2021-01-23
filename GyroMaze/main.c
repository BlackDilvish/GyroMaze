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

int global_x = 0;
int global_y = 0;
int global_z = 0;

volatile uint8_t RTCounter = 0;
void RTC_IRQHandler()
{
	LPC_RTC->ILR = 1;
	if(appState == GAME_STATE)
		RTCounter++;
}

uint8_t systick_counter = 0;
void SysTick_Handler(void) 
{
	if(systick_counter > 6)
	{
		systick_counter = 0;
	}
	else
	{
		systick_counter++;
	}
}

uint32_t abs0(int val)
{
	return val > 0 ? val : -val;
}

int main()
{
	Joystick_Initialize();
	initUart();
	initGraphics();
	fillWindow(LCDWhite);
	I2CInit();
	initGyro();
	SysTick_Config(1e7);
	
	//LPC_RTC->GPREG0 = 1e7;
	
	initRTC();
	
	drawMainMenu();
	
    int selected_width = 12;
    int selected_height = 12;
	int inited = 0;
    int cellsSize = width * height;


    fillCells(cells, cellsSize);
    initPositions(positions, selected_width, selected_height);

    Stack* stackPtr = &stack;
    Maze* mazePtr = &maze; 
    Player* playerPtr = &player;

    initStack(stackPtr, stackPositions, cellsSize);
    initMaze(mazePtr, cells, visitedPositions, positions, stackPtr, selected_width, selected_height);
    initPlayer(playerPtr, mazePtr);

    generateMaze(mazePtr);

	while(true)
	{
		if(systick_counter != 6)
			continue;
		
		switch(appState)
		{
			case MAIN_MENU_STATE:
			updateMainMenu();
			break;

			case SELECT_SIZE_STATE:
			updateSelectSize();
			break;

			case GAME_STATE:
			if(!inited)
			{
				fillCells(cells, cellsSize);
				initPositions(positions, maze_width, maze_height);
				initMaze(mazePtr, cells, visitedPositions, positions, stackPtr, maze_width, maze_height);
				generateMaze(mazePtr);
				initPlayer(playerPtr, mazePtr);
				RTCounter = 0;
				inited = 1;
				drawMaze(mazePtr, 240, 320);
				horizontalMoveDirection = 0;
				verticalMoveDirection = 0;
			}
			
				if(isMazeSolved(playerPtr))
				{
					appState = MAIN_MENU_STATE; //przenosimy do main menu
					drawMainMenu();
					inited = 0;
					if(RTCounter < LPC_RTC->GPREG0)
					{
						//nowy najlepszy czas
						LPC_RTC->GPREG0 = RTCounter;
					}
				}
				else
				{
					drawPlayer(playerPtr, 240, 320);
				}	
			
				switch(Joystick_GetState())
				{
					case JOYSTICK_UP:
					if(checkIfCouldMove(MOVE_TOP, playerPtr))
					{
						cleanPlayer(playerPtr->position, mazePtr, 240, 320);
						movePlayer(MOVE_TOP, playerPtr);
					}
					writeString("JOYSTICK_UP");
					BUTTON_DELAY;
					break;
					
					case JOYSTICK_DOWN:
					if(checkIfCouldMove(MOVE_DOWN, playerPtr))
					{
						cleanPlayer(playerPtr->position, mazePtr, 240, 320);
						movePlayer(MOVE_DOWN, playerPtr);
					}
					writeString("JOYSTICK_DOWN");
					BUTTON_DELAY;
					break;
					
					case JOYSTICK_LEFT:
					if(checkIfCouldMove(MOVE_LEFT, playerPtr))
					{
						cleanPlayer(playerPtr->position, mazePtr, 240, 320);
						movePlayer(MOVE_LEFT, playerPtr);
					}
					writeString("JOYSTICK_LEFT");
					BUTTON_DELAY;
					break;
					
					case JOYSTICK_RIGHT:
					if(checkIfCouldMove(MOVE_RIGHT, playerPtr))
					{
						cleanPlayer(playerPtr->position, mazePtr, 240, 320);						
						movePlayer(MOVE_RIGHT, playerPtr);
					}
						writeString("JOYSTICK_RIGHT");
					BUTTON_DELAY;
					break;
				}

			{
				
			Coordinates coords;
			getData(&coords);

			char buffer[50];
			sprintf(buffer, "x: %d, y: %d, z: %d", abs0(coords.x) > 10000 ? coords.x : 0, abs0(coords.y) > 10000 ? coords.y : 0, abs0(coords.z) > 10000 ? coords.z : 0);
			writeString(buffer);
				
			if(coords.y > 1000)
				global_y++;
			else if(coords.y < -1000)
				global_y--;
			
			if(coords.z > 1000)
				global_z++;
			else if(coords.z < -1000)
				global_z--;
				
			sprintf(buffer,"gy: %d, gz: %d", global_y, global_z);
			writeString(buffer);
			
			if(global_y > 0)
			{
				if(checkIfCouldMove(MOVE_TOP, playerPtr))
					{
						cleanPlayer(playerPtr->position, mazePtr, 240, 320);
						movePlayer(MOVE_TOP, playerPtr);
					}
					writeString("GYRO_UP");
					BUTTON_DELAY;
			}
			else
			{
				if(checkIfCouldMove(MOVE_DOWN, playerPtr))
					{
						cleanPlayer(playerPtr->position, mazePtr, 240, 320);
						movePlayer(MOVE_DOWN, playerPtr);
					}
					writeString("GYRO_DOWN");
					BUTTON_DELAY;
			}
			
			if(global_z > 0)
			{
				if(checkIfCouldMove(MOVE_LEFT, playerPtr))
					{
						cleanPlayer(playerPtr->position, mazePtr, 240, 320);
						movePlayer(MOVE_LEFT, playerPtr);
					}
					writeString("GYRO_LEFT");
					BUTTON_DELAY;
			}
			else
			{
				if(checkIfCouldMove(MOVE_RIGHT, playerPtr))
					{
						cleanPlayer(playerPtr->position, mazePtr, 240, 320);						
						movePlayer(MOVE_RIGHT, playerPtr);
					}
						writeString("JOYSTICK_RIGHT");
					BUTTON_DELAY;
			}
			}
			break;
			
			case LEADERBOARD_STATE:
			updateLeaderboard();
			break;

			default:
			break;
		}
	}
}
