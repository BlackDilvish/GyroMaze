#include "maze.h"

int maze_arr[24][32];

void init_maze()
{
	for(int i = 0; i < sizeX; ++i)
	{
			for(int j = 0; j < sizeY; ++j)
			{
				maze_arr[i][j] = ((4000 * i + 2000 * j) / 12120) % 2;
			}
	}
}

void draw_maze()
{
	for(int i = 0; i < sizeX; ++i)
	{
		for(int j = 0; j < sizeY; ++j)
		{
			int color = LCDWhite;
			if(maze_arr[i][j] == 1)
			{
				color = LCDGinger;
			}
			
			drawSquare(i * 10, j * 10, 10, color); //typedef
		}
	}
}
