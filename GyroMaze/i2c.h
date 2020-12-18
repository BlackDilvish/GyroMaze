#ifndef I2C_H  
#define I2C_H 

#define BUFSIZE						0x20 
#define MAX_TIMEOUT				0x00FFFFFF

#define I2C_IDLE						0 
#define I2C_STARTED				1 
#define I2C_RESTARTED			2 
#define I2C_REPEATED_START	3 
#define DATA_ACK					4 
#define DATA_NACK					5 

void I2CInit(); 
bool I2CStart(); 
void startMasterTransmit(uint8_t* data, uint32_t length);
void startMasterReceive(uint32_t length);
void I2C0_IRQHandler(); 
uint8_t* getReceivedData();
void I2CStop(); 

#endif