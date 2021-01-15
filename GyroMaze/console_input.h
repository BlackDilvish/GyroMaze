#ifndef CONSOLE_INPUT_H
#define CONSOLE_INPUT_H

#include <stdio.h>
#include "player.h"

char getInput()
{
    char inputLetter;
    printf("Prosze podac ruch [W-S-A-D], x - wyjscie: \n");
    scanf("%c", &inputLetter);

    return inputLetter;
}

void consoleMove(char inputLetter, Player* player)
{
    switch(inputLetter)
    {
        case 'w':
            if(checkIfCouldMove(MOVE_TOP, player))
                movePlayer(MOVE_TOP, player);
            return;
        break;


        case 's':
            if(checkIfCouldMove(MOVE_DOWN, player))
                movePlayer(MOVE_DOWN, player);
            return;
        break;

        case 'a':
            if(checkIfCouldMove(MOVE_LEFT, player))
                movePlayer(MOVE_LEFT, player);
            return;
        break;

        case 'd':
            if(checkIfCouldMove(MOVE_RIGHT, player))
                movePlayer(MOVE_RIGHT, player);
            return;
        break;
    }

    printf("Nie wykonano ruchu, sciana?\n");
}

#endif