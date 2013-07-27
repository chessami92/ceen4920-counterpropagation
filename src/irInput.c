#include "history.h"




#include <stdio.h>

const int HISTORY_AMOUNTS[NUM_HISTORY_COUNTS] = {8, 16, HISTORY_SIZE};

void addHistory( History *history, char currentState ) {
    int i;
    unsigned char *irHistory;
    char carryIn, carryOut;

    irHistory = history->irHistory;
    carryIn = ( currentState ? 1 : 0 );

    for( i = 0; i < NUM_HISTORY_COUNTS; ++i ) {
        history->historyCount[i] += carryIn - ( irHistory[HISTORY_AMOUNTS[i] - 1    ] >> 7 );
    }

    for( i = 0; i < HISTORY_SIZE; ++i ) {
        carryOut = irHistory[i] >> 7;
        irHistory[i] = irHistory[i] << 1 | carryIn;
        carryIn = carryOut;
    }
}

