#include "LPC17xx.h"                    // Device header
#include "PIN_LPC17xx.h"
#include "graphics.h"
#include "maze.h"


int main()
{
	initGraphics();
	init_maze();
	draw_maze();
	while(true);
}
