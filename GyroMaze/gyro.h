#ifndef GYRO_H
#define GYRO_H

typedef struct
{
	uint16_t x = 0;
	uint16_t y = 0;
	uint16_t z = 0;
}Coordinates;

void initGyro();
void getData(Coordinates* coords);

#endif