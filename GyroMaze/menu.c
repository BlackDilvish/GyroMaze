#include "Board_Joystick.h"
#include "graphics.h"
#include "menu.h"
#include "uart.h"
#include <stdio.h>

int8_t appState = 0;
int8_t verticalKeyCounter = 0;
int8_t horizontalKeyCounter = 0;
int8_t maze_width = 0;
int8_t maze_height = 0;

void updateMainMenu(void)
{
	switch(Joystick_GetState())
	{
		case JOYSTICK_UP:
		verticalKeyCounter = 0;
		drawMainMenu();
		writeString("JOYSTICK_UP");
		BUTTON_DELAY;
		break;
		
		case JOYSTICK_DOWN:
		verticalKeyCounter = 1;
		drawMainMenu();
		writeString("JOYSTICK_DOWN");
		BUTTON_DELAY;
		break;
		
		case JOYSTICK_CENTER:
		writeString("JOYSTICK_CENTER");
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
	char buffer[4];
	sprintf(buffer, "%d vert", verticalKeyCounter);
	writeString(buffer);
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
	char buffer[16];
	
	switch(verticalKeyCounter)
	{
		case 0:
		fillWindow(LCDWhite);
		drawRectangle(50, 50, 8, 16, LCDYellow);
		drawRectangle(58, 50, 24, 16, LCDBlue);
		drawRectangle(82, 50, 8, 16, LCDBlue);
		drawRectangle(100, 100, 40, 20, LCDBlue);
		sprintf(buffer, "%d x %d", maze_width, maze_height);
		drawString(50, 50, buffer, LCDBlack);
		drawString(100, 100, "Wroc", LCDBlack);
		break;
		
		case 1:
		fillWindow(LCDWhite);
		drawRectangle(50, 50, 8, 16, LCDBlue);
		drawRectangle(58, 50, 24, 16, LCDBlue);
		drawRectangle(82, 50, 8, 16, LCDYellow);
		drawRectangle(100, 100, 40, 20, LCDBlue);
		sprintf(buffer, "%d x %d", maze_width, maze_height);
		drawString(50, 50, buffer, LCDBlack);
		drawString(100, 100, "Wroc", LCDBlack);
		break;

		case 2:
		fillWindow(LCDWhite);
		drawRectangle(50, 50, 8, 16, LCDBlue);
		drawRectangle(58, 50, 24, 16, LCDBlue);
		drawRectangle(82, 50, 8, 16, LCDBlue);
		drawRectangle(150, 100, 40, 20, LCDYellow);
		sprintf(buffer, "%d x %d", maze_width, maze_height);
		drawString(50, 50, buffer, LCDBlack);
		drawString(100, 100, "Wroc", LCDBlack);
		break;
		
		default:
		break;
	}
}
