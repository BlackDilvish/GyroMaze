#include "LPC17xx.h"                    // Device header
#include "PIN_LPC17xx.h"
#include "graphics.h"
#include "maze.h"
#include "i2c.h"
#include "uart.h"
#include "gyro.h"

int main()
{
	initUart();
	I2CInit();
	initGyro();
	
	while(true)
	{
		Coordinates coords;
		getData(&coords);
		
		char buffer[50];
		sprintf(buffer, "x: %d, y: %d, z: %d", coords.x, coords.y, coords.z);
		writeString(buffer);
		
		for(int i=0; i<500000; i++);
	}
}
