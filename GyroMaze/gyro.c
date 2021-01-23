#include "i2c.h"
#include "gyro.h"

#include "graphics.h"

int8_t horizontalMoveDirection = 0;
int8_t verticalMoveDirection = 0;

void initGyro()
{
	uint8_t data[2] = {0x20, 0x0F};
	startMasterTransmit(data, 2);
	I2C_WAIT;
	
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
	
	volatile int8_t* data = getReceivedData();
	
	coords->x = data[1]<<8 | data[0];
	coords->y = data[3]<<8 | data[2];
	coords->z = data[5]<<8 | data[4];

/*	uint8_t addr[1] = {0x28};
	startMasterTransmit(addr, 1);
	I2C_WAIT;
	startMasterReceive(1);
	I2C_WAIT;
	volatile int8_t* data = getReceivedData();
	int x1 = data[0];
	
	addr[0] = 0x29;
	startMasterTransmit(addr, 1);
	I2C_WAIT;
	startMasterReceive(1);
	I2C_WAIT;
	data = getReceivedData();
	int x2 = data[0] << 8;
	
	addr[0] = 0x2A;
	startMasterTransmit(addr, 1);
	I2C_WAIT;
	startMasterReceive(1);
	I2C_WAIT;
	data = getReceivedData();
	int y1 = data[0];
	
	addr[0] = 0x2B;
	startMasterTransmit(addr, 1);
	I2C_WAIT;
	startMasterReceive(1);
	I2C_WAIT;
	data = getReceivedData();
	int y2 = data[0] << 8;
	
	addr[0] = 0x2C;
	startMasterTransmit(addr, 1);
	I2C_WAIT;
	startMasterReceive(1);
	I2C_WAIT;
	data = getReceivedData();
	int z1 = data[0];
	
	addr[0] = 0x2D;
	startMasterTransmit(addr, 1);
	I2C_WAIT;
	startMasterReceive(1);
	I2C_WAIT;
	data = getReceivedData();
	int z2 = data[0] << 8;
	
	coords->x = x1 | x2;
	coords->y = y1 | y2;
	coords->z = z1 | z2;*/
	
}

void predictPlayerMove(Coordinates* coords)
{
	const uint32_t boundaryValue = 20000;
	horizontalMoveDirection = 0;
	verticalMoveDirection = 0;

	if(coords->y > boundaryValue)
		verticalMoveDirection = 1;
	else if(coords->y < -boundaryValue)
		verticalMoveDirection = -1;

	if(coords->z > boundaryValue)
		horizontalMoveDirection = 1;
	else if(coords->z < -boundaryValue)
		horizontalMoveDirection = -1;
}
