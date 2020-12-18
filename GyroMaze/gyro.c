#include "i2c.h"
#include "gyro.h"

void initGyro()
{
	uint8_t data[2] = {0x20, 0x0F};
	startMasterTransmit(data, 2);
	//wait => while(!(LPC_I2C0->I2CONSET & (1<<4))); ???
	
	data = {0x21, 0x00};
	startMasterTransmit(data, 2);
	//wait
	
	data = {0x22, 0x08};
	startMasterTransmit(data, 2);
	//wait
	
	data = {0x23, 0x00};
	startMasterTransmit(data, 2);
	//wait
	
	data = {0x24, 0x00};
	startMasterTransmit(data, 2);
	//wait
}

void getData(Coordinates* coords)
{
	uint8_t addr[1] = {0xA8};
	startMasterTransmit(addr, 1);
	//wait
	
	startMasterReceive(6);
	//wait
	
	uint16_t* data = (uint16_t*) getReceivedData();
	
	coords->x = data[0];
	coords->y = data[1];
	coords->z = data[2];
	return coords;
}
