#include <stdlib.h>
#include <assert.h>
#include "persistence.h"

static char *testFile = "test_definition";

static void cannotOpenFile_test( void ) {
    int weights[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    assert( persistNetwork( 1, 2, 3, weights ) == 0 && "Shouldn't be able to open null file" );
}

static void initPersistence_test( void ) {
    char *argv[4] = {"", "", testFile, "" };
    initPersistence( 4, argv );
}

static void persistAndLoad_test() {
    int weights[8];
    int input = 1, hidden = 2, output = 3;
    int i;

    for( i = 0; i < 8; ++i ) {
        weights[i] = i;
    }

    assert( persistNetwork( input, hidden, output, weights ) == 1 );

    input = 0; hidden = 0; output = 0;

    for( i = 0; i < 8; ++i ) {
        weights[i] = 0;
    }
    assert( retrieveNetwork( &input, &hidden, &output, weights ) == 1 );
    assert( input == 1 && "Input should be re-initialized" );
    assert( hidden == 2 && "Hidden should be re-initialized" );
    assert( output == 3 && "Output should be re-initialized" );
    for( i = 0; i < 8; ++i ) {
        assert( weights[i] == i && "Weights should be re-initialized" );
    }
}

int main( void ) {
    cannotOpenFile_test();
    initPersistence_test();
    persistAndLoad_test();

    remove( testFile );

    exit( EXIT_SUCCESS );
}
