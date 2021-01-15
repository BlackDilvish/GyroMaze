#ifndef MAZE_H
#define MAZE_H

 //ta strukturka słuzy do okreslenia gdzie bd sciany, uzywajac pol bitowych, aktualnie jednak (i wydaje mi sie ze to wystarczy)
 //przechowywac cztery stany: 00->brak scian, 01 sciana z prawej, 10 sciana z dolu 11 sciana z dolu i prawej, sciany gorne i lewe
 //bd uwzgledniane przez sasiednie komorki, mozna tez ustalic ze np cala gora ma sciany i caly dol, ale to zobaczy sie
typedef struct CellStruct
{
    int walls : 4;
} Cell;

//struktura oznacza punkt (pozycje), wykorzystywana m.in. na stosie
typedef struct PositionStruct
{
    int x : 6;
    int y : 6;
} Position;

//stos - ma aktualny rozmiar i maksymalny rozmiar oraz wskaznik do pozycji (wczesniej STATYCZNIE utworzonej tablicy struktur), tablica
//pozycji sluzy oczywiscie do odkladania zgodnie z algorytmem pozycji na stosie
typedef struct StackStruct
{
    int currentSize;
    int maxSize;
    Position* positions;
} Stack;

//labirynt - przechowuje wszystkie pozycje, pozycje odwiedzone, wysokosc, szerokosc oraz stos i komórki (informacje o ściankach 
//sluzace do narysowania labiryntu pozniej)
typedef struct MazeStruct
{
    int width : 6;
    int height : 6;
    Cell* cells;
    Stack* stack;
    Position* positions;
    Position* visitedPositions;
    Position start;
    Position destination;
} Maze;

//funkcje

void clearCells(Cell* cells, int size); //ustawia 00 na sciankach
Cell findCellByPosition(Maze* mazePtr, Position position);
int hasRightBorder(Cell cell);
int hasDownBorder(Cell cell);
int notWithinBounds(int value, int max);

void initPositions(Position* positions, int width, int height); //ustawia pozycje rosnaco od lewego gornego rogu, tj. na grafice

//otrzymujemy statycznie utworzone w mainie tablice i inicjalizujemy labirynt (ustalamy stos, tablice pozycji, wymiary itp.)
void initMaze(Maze* mazePtr, Cell* cells, Position* visitedPositions, Position* positions, Stack* stackPtr, int width, int height);
//ta funkcja ma za zadanie korzystajac z mazePtr->visitedPositions zapelnic scianki w cell->walls, dzieki czemu bedzie mozna pozniej
//narysowac labirynt
void generateMaze(Maze* mazePtr);
//tablica pozycji jest jednowymiarowa (width x height), wiec trzeba zmapowac
int getIndexFromPosition(Position position, int width, int height);
//a tutaj odwrotnie
Position getPositionFromIndex(int index, int width, int height);
//tutaj coś w rodzaju pseudokonstruktora dla pozycji
Position preparePosition(int x, int y);
//operacje na pozycjach (wektorach)
Position addPositions(Position first, Position second);

//operacje na stosie:
void initStack(Stack* stackPtr, Position* stackPositions, int size);
void stackPush(Stack* stackPtr, Position newPosition);
Position stackPop(Stack* stackPtr);
int stackEmpty(Stack* stack);
//

int getUnvisitedNeighbor(Position position, Position* mazeVisitedPositions, int visitedCounter, int width, int height);
int positionsCompare(Position position1, Position position2);
int inMazeBoundaries(Position position, int mazeWidth, int mazeHeight);
int notInVisitedPositions(Position* visitedPositions, Position potentialNeighbor, int visitedCounter);
void getPotentialNeighborsInRandomOrder(Position* neighbors, Position position);
int getNeighborIndex(int* possibleIndexes, int moduloValue);

void swapArrayElements(int* arr, int index1, int index2);

//dosc istotna funkcja, wykorzystuje generator pseudolosowy (ale nie rand) silnie oparty co do wyboru wartosci na generatorze
//ze statystyki z drugiego semestru od Pana Gołaszewskiego
int generateRandomValue();
//czesc zadan bezposrednio zwiazanych z wpisywaniem wartości ścianek z generateMaze trafia do tej funkcji
//jest wywolywana w generateMaze
void setWalls(Maze* mazePtr, Position previousPosition, Position currentPosition);

#endif