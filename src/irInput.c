#include "history.h"

const int HISTORY_AMOUNTS[NUM_HISTORY_COUNTS] = {8, 16, HISTORY_SIZE - 1};

void addHistory( History *history, char currentState ) {
    int i;
    unsigned char *irHistory;
    int historyIndex;

    irHistory = history->irHistory;
    currentState = ( currentState ? 1 : 0 );

    for( i = 0; i < NUM_HISTORY_COUNTS; ++i ) {
        historyIndex = history->currentHistory - HISTORY_AMOUNTS[i];
        if( historyIndex < 0 ) {
            historyIndex += HISTORY_SIZE;
        }
        history->historyCount[i] += currentState - ( ( irHistory[historyIndex] >> ( 7 - history->currentBit ) ) & 0x01 );
    }

    irHistory[history->currentHistory] <<= 1;
    irHistory[history->currentHistory] |= currentState;

    history->currentBit = ( history->currentBit + 1 ) % 8;
    if( !history->currentBit ) {
        history->currentHistory = ( history->currentHistory + 1 ) % HISTORY_SIZE;
    }
}

