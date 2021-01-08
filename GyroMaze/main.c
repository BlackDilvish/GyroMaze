#include "LPC17xx.h"                    // Device header
#include "PIN_LPC17xx.h"
#include <stdio.h>
#include "graphics.h"
#include "maze.h"
#include "i2c.h"
#include "uart.h"
#include "gyro.h"

int main()
{
	initUart();
	writeString("Start");
	initGraphics();
	fillWindow(LCDWhite);
	drawString(20, 20, "xd2", LCDBlack);
	I2CInit();
	drawString(20, 40, "xd3", LCDBlack);
	initGyro();
	drawString(20, 60, "xd4", LCDBlack);

	while(true)
	{
		Coordinates coords;
		drawString(20, 80, "xd5", LCDBlack);
		getData(&coords);
		drawString(20, 100, "xd6", LCDBlack);

		char buffer[50];
		sprintf(buffer, "x: %d, y: %d, z: %d", coords.x, coords.y, coords.z);
		writeString(buffer);
		fillWindow(LCDWhite);
		drawString(20, 20, buffer, LCDBlack);

		for(int i=0; i<500000; i++);
	}
}
