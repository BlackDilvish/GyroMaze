#include "maze.h"
#include "maze_utility.h"

//Mamy statycznie zaalokowana pamiec na maksymalnie duzy labirynt (30 x 30)
//ale z reguly wystarczy skorzystac tylko z kawalka tablicy

#define width 30 //to są maksymalne wartości
#define height 30 //to są maksymalne wartosci

int main(void)
{
    //to tylko dla testowania w konsoli
    int selected_width;
    int selected_height;

    printf("Prosze podac szerokosc: \n");
    scanf("%d", &selected_width);
    printf("Prosze podac wysokosc: \n");
    scanf("%d", &selected_height);
    //to tylko dla testowania w konsoli

    //przygotowujemy pamięć statyczną
    int cellsSize = width * height;
    Stack stack;
    Maze maze;
    Cell cells[width * height];
    Position positions[width * height]; 
    Position stackPositions[width * height];//ta tablica będzie działać jak stos do zapamiętywania ostatnio odwiedzonych pozycji
    Position visitedPositions[width * height];

    clearCells(cells, cellsSize);
    initPositions(positions, selected_width, selected_height);

    //wskaźniki do statycznie alokowanej pamięci
    Stack* stackPtr = &stack;
    Maze* mazePtr = &maze; 

    initStack(stackPtr, stackPositions, cellsSize);
    initMaze(mazePtr, cells, visitedPositions, positions, stackPtr, selected_width, selected_height);

    generateMaze(mazePtr);

    //tutaj narysować tam gdzie są połączenia albo na odwrót
    drawMaze(mazePtr);

    return 0;
}