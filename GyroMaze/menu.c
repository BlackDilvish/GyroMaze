#include "Board_Joystick.h"
#include "graphics.h"
#include "menu.h"

uint8_t appState = 0;
uint8_t verticalKeyCounter = 0;
uint8_t horizontalKeyCounter = 0;
uint8_t maze_width = 0;
uint8_t maze_height = 0;

void updateMainMenu(void)
{
	switch(Joystick_GetState())
	{
		case JOYSTICK_UP:
		verticalKeyCounter = 0;
		drawMainMenu();
		BUTTON_DELAY;
		break;
		
		case JOYSTICK_DOWN:
		verticalKeyCounter = 1;
		drawMainMenu();
		BUTTON_DELAY;
		break;
		
		case JOYSTICK_CENTER:
		if (verticalKeyCounter == 0)
		{
			appState = GAME_STATE;
			//draw maze
		}
		else
		{
			verticalKeyCounter = 0;
			horizontalKeyCounter = 0;
			appState = SELECT_SIZE_STATE;
			drawSelectSize();
		}
		BUTTON_DELAY;
		break;
		
		default:
		break;
	}
}

void updateSelectSize(void)
{
	switch(Joystick_GetState())
	{
		case JOYSTICK_UP:
		if (--verticalKeyCounter < 0) verticalKeyCounter = 0;
		drawSelectSize();
		BUTTON_DELAY;
		break;
		
		case JOYSTICK_DOWN:
		if (++verticalKeyCounter > 30) verticalKeyCounter = 30;
		drawSelectSize();
		BUTTON_DELAY;
		break;
		
		case JOYSTICK_CENTER:
		switch(horizontalKeyCounter)
		{
			case 0:
			maze_width = verticalKeyCounter;
			horizontalKeyCounter++;
			drawSelectSize();
			break;

			case 1:
			maze_height = verticalKeyCounter;
			horizontalKeyCounter++;
			drawSelectSize();
			break;

			case 2:
			appState = MAIN_MENU_STATE;
			verticalKeyCounter = 0;
			horizontalKeyCounter = 0;
			drawMainMenu();
			break;
		}
		BUTTON_DELAY;
		break;
		
		default:
		break;
	}
}

void drawMainMenu(void)
{
	switch(verticalKeyCounter)
	{
		case 0:
		fillWindow(LCDWhite);
		drawRectangle(50, 50, 100, 30, LCDYellow);
		drawRectangle(50, 100, 100, 30, LCDBlue);
		drawString(50, 50, "Nowa gra", LCDBlack);
		drawString(50, 100, "Zmien rozmiar", LCDBlack);
		break;
		
		case 1:
		fillWindow(LCDWhite);
		drawRectangle(50, 50, 100, 30, LCDBlue);
		drawRectangle(50, 100, 100, 30, LCDYellow);
		drawString(50, 50, "Nowa gra", LCDBlack);
		drawString(50, 100, "Zmien rozmiar", LCDBlack);
		break;
		
		default:
		break;
	}
}

void drawSelectSize(void)
{
	switch(verticalKeyCounter)
	{
		case 0:
		fillWindow(LCDWhite);
		drawSquare(50, 50, 32, LCDYellow);
		drawSquare(82, 50, 48, LCDBlue);
		drawSquare(130, 50, 32, LCDBlue);
		drawRectangle(100, 100, 40, 20, LCDBlue);
		char buffer[16];
		sprintf(buffer, "%d x %d", maze_width, maze_height);
		drawString(50, 50, buffer, LCDBlack);
		drawString(100, 100, "Wroc", LCDBlack);
		break;
		
		case 1:
		fillWindow(LCDWhite);
		drawSquare(50, 50, 32, LCDBlue);
		drawSquare(82, 50, 48, LCDBlue);
		drawSquare(130, 50, 32, LCDYellow);
		drawRectangle(100, 100, 40, 20, LCDBlue);
		char buffer[16];
		sprintf(buffer, "%d x %d", maze_width, maze_height);
		drawString(50, 50, buffer, LCDBlack);
		drawString(100, 100, "Wroc", LCDBlack);
		break;

		case 2:
		fillWindow(LCDWhite);
		drawSquare(50, 50, 32, LCDBlue);
		drawSquare(82, 50, 48, LCDBlue);
		drawSquare(130, 50, 32, LCDBlue);
		drawRectangle(150, 100, 40, 20, LCDYellow);
		char buffer[16];
		sprintf(buffer, "%d x %d", maze_width, maze_height);
		drawString(50, 50, buffer, LCDBlack);
		drawString(100, 100, "Wroc", LCDBlack);
		break;
		
		default:
		break;
	}
}
