#include "Board_Joystick.h"
#include "graphics.h"
#include "menu.h"
#include "uart.h"
#include <stdio.h>

int8_t appState = 0;
int8_t verticalKeyCounter = 0;
int8_t horizontalKeyCounter = 0;
int8_t maze_width = 10;
int8_t maze_height = 10;

void updateMainMenu(void)
{
	switch(Joystick_GetState())
	{
		case JOYSTICK_UP:
		if(--verticalKeyCounter < 0) verticalKeyCounter = 0;
		drawMainMenu();
		BUTTON_DELAY;
		break;
		
		case JOYSTICK_DOWN:
		if (++verticalKeyCounter > 2) verticalKeyCounter = 2;
		drawMainMenu();
		BUTTON_DELAY;
		break;
		
		case JOYSTICK_CENTER:
		if (verticalKeyCounter == 0)
		{
			appState = GAME_STATE;
			//draw maze
		}
		else if (verticalKeyCounter == 1)
		{
			verticalKeyCounter = 0;
			horizontalKeyCounter = 0;
			appState = SELECT_SIZE_STATE;
			drawSelectSize();
		}
		else
		{
			appState = LEADERBOARD_STATE;
			drawLeaderboard();
		}
		BUTTON_DELAY;
		break;
		
		default:
		break;
	}
}

void updateSelectSize(void)
{
	char buffer[8];
	sprintf(buffer, "%d vert", verticalKeyCounter);
	writeString(buffer);
	switch(Joystick_GetState())
	{
		case JOYSTICK_DOWN:
		if (--verticalKeyCounter < 0) verticalKeyCounter = 0;
		drawSelectSize();
		BUTTON_DELAY;
		break;
		
		case JOYSTICK_UP:
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

void updateLeaderboard(void)
{
	switch (Joystick_GetState())
	{
	case JOYSTICK_CENTER:
		appState = MAIN_MENU_STATE;
		drawMainMenu();
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
		drawRectangle(50, 150, 100, 30, LCDBlue);
		drawString(50, 50, "Nowa gra", LCDBlack);
		drawString(50, 100, "Zmien rozmiar", LCDBlack);
		drawString(50, 150, "Najlepsze wyniki", LCDBlack);
		break;
		
		case 1:
		fillWindow(LCDWhite);
		drawRectangle(50, 50, 100, 30, LCDBlue);
		drawRectangle(50, 100, 100, 30, LCDYellow);
		drawRectangle(50, 150, 100, 30, LCDBlue);
		drawString(50, 50, "Nowa gra", LCDBlack);
		drawString(50, 100, "Zmien rozmiar", LCDBlack);
		drawString(50, 150, "Najlepsze wyniki", LCDBlack);
		break;
		
		case 2:
		fillWindow(LCDWhite);
		drawRectangle(50, 50, 100, 30, LCDBlue);
		drawRectangle(50, 100, 100, 30, LCDBlue);
		drawRectangle(50, 150, 100, 30, LCDYellow);
		drawString(50, 50, "Nowa gra", LCDBlack);
		drawString(50, 100, "Zmien rozmiar", LCDBlack);
		drawString(50, 150, "Najlepsze wyniki", LCDBlack);
		break;
		
		default:
		break;
	}
}

void drawSelectSize(void)
{
	char buffer[16];
	
	switch(horizontalKeyCounter)
	{
		case 0:
		fillWindow(LCDWhite);
		drawRectangle(50, 50, 8, 16, LCDYellow);
		drawRectangle(58, 50, 24, 16, LCDBlue);
		drawRectangle(82, 50, 8, 16, LCDBlue);
		drawRectangle(100, 100, 40, 20, LCDBlue);
		sprintf(buffer, "%d x %d", verticalKeyCounter, maze_height);
		drawString(50, 50, buffer, LCDBlack);
		drawString(100, 100, "Wroc", LCDBlack);
		break;
		
		case 1:
		fillWindow(LCDWhite);
		drawRectangle(50, 50, 8, 16, LCDBlue);
		drawRectangle(58, 50, 24, 16, LCDBlue);
		drawRectangle(82, 50, 8, 16, LCDYellow);
		drawRectangle(100, 100, 40, 20, LCDBlue);
		sprintf(buffer, "%d x %d", maze_width, verticalKeyCounter);
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

void drawLeaderboard(void)
{
	fillWindow(LCDWhite);
	char buffer[32];
	sprintf(buffer, "Najlepszy czas: %d s", LPC_RTC->GPREG0);
	writeString(buffer);
	
	drawRectangle(50, 50, 150, 50, LCDBlue);
	drawRectangle(100, 150, 50, 20, LCDYellow);
	drawString(50, 50, buffer, LCDBlack);
	drawString(100, 150, "Wroc", LCDBlack);
}
