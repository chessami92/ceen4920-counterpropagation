#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "history.h"

static void increasingHistoryCounts( void ) {
    int i;

    for( i = 0; i < NUM_HISTORY_COUNTS - 1; ++i ) {
        assert( HISTORY_AMOUNTS[i] < HISTORY_AMOUNTS[i + 1] && "History amounts should be monotonically increasing" );
    }
}

static void historyAdjustment( void ) {
    History history = {{0, 0}, {0, 0}, 0, 0};
    int i;

    for( i = 0; i < HISTORY_SIZE; ++i ) {
        history.irHistory[i] = 0;
    }
    for( i = 0; i < NUM_HISTORY_COUNTS; ++i ) {
        history.historyCount[i] = 0;
    }
    addHistory( &history, 4 );
    assert( history.irHistory[0] == 1 && history.historyCount[0] == 1 );

    for( i = 0; i < 8; ++i ) {
        addHistory( &history, 1 );
    }
    assert( history.irHistory[0] == 0xff && history.irHistory[1] == 1 && history.historyCount[0] == 9 );

    for( i = 0; i < 56; ++i ) {
        addHistory( &history, 1 );
    }
    assert( history.historyCount[0] == 64 && history.historyCount[1] == 65 && history.historyCount[2] == 65 );

    for( i = 0; i < 64; ++i ) {
        addHistory( &history, 1 );
    }
    assert( history.historyCount[0] == 64 && history.historyCount[1] == 128 && history.historyCount[2] == 129 );

    for( i = 0; i < 500; ++i ) {
        addHistory( &history, 1 );
    }
    assert( history.historyCount[0] == 64 && history.historyCount[1] == 128 && history.historyCount[2] == 504 );

    for( i = 0; i < 64; ++i ) {
        addHistory( &history, 0 );
    }
    assert( history.historyCount[0] == 0 && history.historyCount[1] == 64 && history.historyCount[2] == 440 );

    for( i = 0; i < 64; ++i ) {
        addHistory( &history, 0 );
    }
    assert( history.historyCount[0] == 0 && history.historyCount[1] == 0 && history.historyCount[2] == 376 );

    for( i = 0; i < 376; ++i ) {
        addHistory( &history, 0 );
    }
    assert( history.historyCount[0] == 0 && history.historyCount[1] == 0 && history.historyCount[2] == 0 );
}

int main( void ) {
    increasingHistoryCounts();
    historyAdjustment();

    exit( EXIT_SUCCESS );
}

