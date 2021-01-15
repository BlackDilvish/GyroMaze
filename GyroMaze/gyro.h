#ifndef GYRO_H
#define GYRO_H

#include "stdint.h"
#include "LPC17xx.h"
#include "PIN_LPC17xx.h"

typedef struct
{
	int16_t x;
	int16_t y;
	int16_t z;
}Coordinates;

void initGyro();
void getData(Coordinates* coords);

#endif