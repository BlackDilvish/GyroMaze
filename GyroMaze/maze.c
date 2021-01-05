#include "maze.h"

void clearCells(Cell* cells, int size)
{
    for(int i = 0; i < size; ++i)
    {
        cells[i].walls = 0;
    }
}

void initPositions(Position* positions, int width, int height)
{
    int size = width * height;

    for(int i = 0; i < size; ++i)
    {
        positions[i] = getPositionFromIndex(i, width, height);
    }
}

void initMaze(Maze* mazePtr, Cell* cells, Position* visitedPositions, Position* positions, Stack* stack, int width, int height)
{
    mazePtr->width = width;
    mazePtr->height = height;
    mazePtr->cells = cells;
    mazePtr->stack = stack;
    mazePtr->positions = positions;
    mazePtr->visitedPositions = visitedPositions;
}

void generateMaze(Maze* mazePtr)
{
    int visitedCounter = 1;
    mazePtr->visitedPositions[visitedCounter - 1] = mazePtr->positions[0];
    int size = mazePtr->width * mazePtr->height;
    int currentIndex = 0;

    while(visitedCounter < size)
    {
        int potentialNeighborIndex = getUnvisitedNeighbor(mazePtr->positions[currentIndex], mazePtr->visitedPositions, visitedCounter,
         mazePtr->width, mazePtr->height);

        if(potentialNeighborIndex > -1)
        {
            currentIndex = potentialNeighborIndex;
            ++visitedCounter;
            mazePtr->visitedPositions[visitedCounter - 1] = mazePtr->positions[currentIndex];
            
            if(!stackEmpty(mazePtr->stack))
            {
                setWalls(mazePtr, mazePtr->stack->positions[mazePtr->stack->currentSize - 1], mazePtr->positions[currentIndex]);
            }

            stackPush(mazePtr->stack, mazePtr->positions[currentIndex]);
        }
        else //nie mamy się gdzie ruszyć trzeba wrócić
        {
            Position previousPosition;

            do
            {
                previousPosition = stackPop(mazePtr->stack);
                int newIndex = getIndexFromPosition(previousPosition, mazePtr->width, mazePtr->height);
                currentIndex = newIndex;
            } while(getUnvisitedNeighbor(previousPosition, mazePtr->visitedPositions, visitedCounter,
            mazePtr->width, mazePtr->height) == -1);            
        }
    }
}

void initStack(Stack* stackPtr, Position* stackPositions, int size)
{
    stackPtr->currentSize = 0;
    stackPtr->maxSize = size;
    stackPtr->positions = stackPositions;
}

void stackPush(Stack* stackPtr, Position newPosition)
{
    stackPtr->currentSize = stackPtr->currentSize + 1;
    stackPtr->positions[stackPtr->currentSize - 1] = newPosition;
}

Position stackPop(Stack* stackPtr)
{
    Position poppedPosition = stackPtr->positions[stackPtr->currentSize - 1];
    stackPtr->currentSize = stackPtr->currentSize - 1;
    return poppedPosition;
}

int stackEmpty(Stack* stack)
{
    return stack->currentSize == 0;
}

int getIndexFromPosition(Position position, int width, int height)
{
    int index = position.y * width + position.x;
    return index;
}

Position getPositionFromIndex(int index, int width, int height)
{
    Position position;
    position.x = index % width;
    position.y = index / width;

    return position;
}

int getUnvisitedNeighbor(Position position, Position* mazeVisitedPositions, int visitedCounter, int width, int height)
{
    Position neighbors[4];
    getPotentialNeighborsInRandomOrder(neighbors, position);

    for(int i = 0; i < 4; ++i)
    {
        if(inMazeBoundaries(neighbors[i], width, height) && notInVisitedPositions(mazeVisitedPositions, neighbors[i], visitedCounter))
        {
            return getIndexFromPosition(neighbors[i], width, height);
        }
    }

    return -1; //nie ma nieodwiedzonych sąsiadów
}

Position preparePosition(int x, int y)
{
    Position position;
    position.x = x;
    position.y = y;

    return position;
}

int positionsCompare(Position position1, Position position2) //zwraca zero gdy pozycje są takie same, zwraca -1 w przeciwnym przypadku
{
    if(position1.x == position2.x && position1.y == position2.y)
    {
        return 0;
    }
    else
    {
        return -1;    
    }   
}

int inMazeBoundaries(Position position, int mazeWidth, int mazeHeight)
{
    if(position.x >= 0 && position.x < mazeWidth && position.y >= 0 && position.y < mazeHeight)
    {
        return 1;
    }
    else
    {
        return 0;   
    }
}

int notInVisitedPositions(Position* visitedPositions, Position potentialNeighbor, int visitedCounter)
{
    for(int i = 0; i < visitedCounter; ++i)
    {
        if(positionsCompare(visitedPositions[i], potentialNeighbor) == 0)
            return 0;
    }

    return 1;
}

void getPotentialNeighborsInRandomOrder(Position* neighbors, Position position)
{
    Position leftPos = preparePosition(position.x - 1, position.y);
    Position rightPos = preparePosition(position.x + 1, position.y);
    Position topPos = preparePosition(position.x, position.y - 1);
    Position downPos = preparePosition(position.x, position.y + 1);

    int possibleIndexes[] = {0, 1, 2, 3};

    int leftPosNeighborIndex = getNeighborIndex(possibleIndexes, 4);
    int rightPosNeighborIndex = getNeighborIndex(possibleIndexes, 3);
    int topPosNeighborIndex = getNeighborIndex(possibleIndexes, 2);
    int downPosNeighborIndex = possibleIndexes[0];

    neighbors[leftPosNeighborIndex] = leftPos;
    neighbors[rightPosNeighborIndex] = rightPos;
    neighbors[topPosNeighborIndex] = topPos;
    neighbors[downPosNeighborIndex] = downPos;
}

void swapArrayElements(int* arr, int index1, int index2)
{
    int temporary = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temporary;    
}

int generateRandomValue()
{
    int a[] = {133333, 3331, 99991};
    int m = 1 << 10;
    static int b = 1337339;
    static int x[] = {1, 2, 3};

    int x_i = 0;

    for(int j = 1; j < 3; ++j)
    {
        x_i += a[j] * x[3 - j] + b;
    }

    x_i = x_i % m;

    x[0] = x[1];
    x[1] = x[2];
    x[2] = x[3];
    x[3] = x_i;

    return x_i;
}

int getNeighborIndex(int* possibleIndexes, int moduloValue)
{
    int indexesArrayIndex = generateRandomValue() % moduloValue;
    int neighborIndex = possibleIndexes[indexesArrayIndex];
    swapArrayElements(possibleIndexes, moduloValue - 1, indexesArrayIndex);

    return neighborIndex;
}

void setWalls(Maze* mazePtr, Position previousPosition, Position currentPosition)
{
    Position positionToSetWalls;

    if(previousPosition.x == currentPosition.x)
    {
        if(previousPosition.y < currentPosition.y)
            positionToSetWalls = previousPosition;
        else positionToSetWalls = currentPosition;

        int index = getIndexFromPosition(positionToSetWalls, mazePtr->width, mazePtr->height);
        mazePtr->cells[index].walls += 2;
    }

    else if(previousPosition.y == currentPosition.y)
    {
        if(previousPosition.x < currentPosition.x)
            positionToSetWalls = previousPosition;
        else positionToSetWalls = currentPosition;

        int index = getIndexFromPosition(positionToSetWalls, mazePtr->width, mazePtr->height);
        mazePtr->cells[index].walls += 1;
    }
}
