#include "graphics.h"

void initGraphics()
{
	lcdConfiguration();
	init_ILI9325();
}

void fillWindow(long color)
{
	lcdWriteReg(ADRX_RAM, 0);
	lcdWriteReg(ADRY_RAM, 0);
	
	lcdWriteReg(DATA_RAM, color);
	
	for(int i = 0; i < LCD_MAX_X * LCD_MAX_Y; ++i)
	{
		lcdWriteData(color);
	}
}

void drawRectangle(int posX, int posY, int sizeX, int sizeY, long color)
{
	for(int i = 0; i < sizeY; ++i)
	{
			lcdWriteReg(ADRX_RAM, posX);
			lcdWriteReg(ADRY_RAM, posY + i);
			lcdWriteReg(DATA_RAM, color);
		
			for(int j = 0; j < sizeX - 1; ++j)
			{
					lcdWriteData(color);
			}
	}
}

void drawSquare(int posX, int posY, int size, long color)
{
	drawRectangle(posX, posY, size, size, color);
}

void drawLine(int pos1X, int pos1Y, int pos2X, int pos2Y, long color)
{
 	int kx = pos1X <= pos2X ? 1 : -1;
	int ky = pos1Y <= pos2Y ? 1 : -1;
	
	int diffX = get_abs(pos1X, pos2X);
	int diffY = get_abs(pos1Y, pos2Y);
	
	lcdWriteReg(ADRX_RAM, pos1X);
	lcdWriteReg(ADRY_RAM, pos1Y);
	
	lcdWriteReg(DATA_RAM, color);
	
	if(diffX < diffY)
	{
		int eps = diffY / 2;

		for(int i = 0; i < diffY; ++i)
		{
			pos1Y += ky;
			eps -= diffX;
			
			if(eps < 0)
			{
				pos1X += kx;
				eps += diffY;
			}
			
			lcdWriteReg(ADRX_RAM, pos1X);
			lcdWriteReg(ADRY_RAM, pos1Y);
	
			lcdWriteReg(DATA_RAM, color);
		}
	} 
	else 
	{
		int eps = diffX / 2;
		for(int i = 0; i < diffX; ++i)
		{
			pos1X += kx;
			eps -= diffY;
			if(eps < 0)
			{
				pos1X += ky;
				eps += diffX;
			}	
				
			lcdWriteReg(ADRX_RAM, pos1X);
			lcdWriteReg(ADRY_RAM, pos1Y);
	
			lcdWriteReg(DATA_RAM, color);
		}
	}
}

int get_abs(int x1, int x2)
{
	int diff = x1 - x2;
	
	return diff >= 0 ? diff : -diff;
}

void drawLiterka(int posX, int posY, char letter, long color)
{
	unsigned char buffor[16];
	GetASCIICode(0, buffor, letter);
	
	for(int i = 0; i < 16; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			if(buffor[i] & (1 << j) )
			{
				lcdWriteReg(ADRX_RAM, posX - j + 8);
				lcdWriteReg(ADRY_RAM, posY + i);
				
				lcdWriteReg(DATA_RAM, color);
			}
		}
	}
}

void drawString(int startX, int startY, const char* str, long color)
{
	int i = 0;
	
	while(str[i] != '\0')
	{
		drawLiterka(startX + i * 8, startY, str[i], color);
		++i;
	}
}
