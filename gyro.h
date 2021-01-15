#ifndef GYRO_H
#define GYRO_H

#include "stdint.h"
#include "LPC17xx.h"
#include "PIN_LPC17xx.h"

typedef struct
{
	uint16_t x;
	uint16_t y;
	uint16_t z;
}Coordinates;

void initGyro();
void getData(Coordinates* coords);

#endif