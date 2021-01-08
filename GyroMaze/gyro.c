#include "i2c.h"
#include "gyro.h"

#include "graphics.h"
void initGyro()
{
	uint8_t data[2] = {0x20, 0x0F};
	startMasterTransmit(data, 2);
	drawString(70, 40, "xd 1.2", LCDBlack);

	I2C_WAIT;
	drawString(70, 60, "xd 1.3", LCDBlack);
	
	data[0] = 0x21;
	data[1] = 0x00;
	startMasterTransmit(data, 2);
	I2C_WAIT;
	
	data[0] = 0x22;
	data[1] = 0x08;
	startMasterTransmit(data, 2);
	I2C_WAIT;
	
	data[0] = 0x23;
	data[1] = 0x00;
	startMasterTransmit(data, 2);
	I2C_WAIT;
	
	data[0] = 0x24;
	data[1] = 0x00;
	startMasterTransmit(data, 2);
	I2C_WAIT;
}

void getData(Coordinates* coords)
{
	uint8_t addr[1] = {0xA8};
	startMasterTransmit(addr, 1);
	I2C_WAIT;
	
	startMasterReceive(6);
	I2C_WAIT;
	
	uint16_t* data = (uint16_t*) getReceivedData();
	
	coords->x = data[0];
	coords->y = data[1];
	coords->z = data[2];
}
