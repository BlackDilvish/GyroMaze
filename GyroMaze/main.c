#include "LPC17xx.h"                    // Device header
#include "PIN_LPC17xx.h"
#include <stdio.h>
#include "graphics.h"
#include "maze.h"
#include "i2c.h"
#include "uart.h"
#include "gyro.h"
#include "menu.h"

int main()
{
	Joystick_Initialize();
	initUart();
	initGraphics();
	fillWindow(LCDWhite);
	I2CInit();
	initGyro();

	drawMainMenu();

	while(true)
	{
		switch(appState)
		{
			case MAIN_MENU_STATE:
			updateMainMenu();
			break;

			case SELECT_SIZE_STATE:
			updateSelectSize();
			break;

			case GAME_STATE:
			Coordinates coords;
			getData(&coords);

			char buffer[50];
			sprintf(buffer, "x: %d, y: %d, z: %d", coords.x, coords.y, coords.z);
			writeString(buffer);
			break;

			default:
			break;
		}

		for(int i=0; i<1000000; i++); //fancy delay
	}
}
