#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "LPC17xx.h"                    // Device header
#include "lcd_lib/Open1768_LCD.h"
#include "lcd_lib/LCD_ILI9325.h"
#include "lcd_lib/asciiLib.h"

typedef struct Vec2
{
	int x;
	int y;
} Vector2;

void initGraphics(void);
void fillWindow(long color);
void drawRectangle(int posX, int posY, int sizeX, int sizeY, long color);
void drawSquare(int posX, int posY, int size, long color);
void drawLine(int pos1X, int pos1Y, int pos2X, int pos2Y, long color);
int get_abs(int x1, int x2);
void drawLiterka(int posX, int posY, char letter, long color);
void drawString(int startX, int startY, const char* str, long color);
void map_to_screen_sizes(void);

#endif
