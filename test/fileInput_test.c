#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "counterprop.h"
#include "input.h"

extern char *inputFile;

char *inputFile;

static void initInput_test( void ) {
    FILE *fd;

    fd = fopen( inputFile, "w" );
    fprintf( fd, "%d %d %d %d\n", 0, 1, 2, 3);
    fprintf( fd, "%d %d %d %d\n", 4, 5, 6, 7);
    fprintf( fd, "EOF" );
    fclose( fd );
}

static void populateNextTestCase_test( void ) {
    Network *network;
    int i;

    network = makeNetwork( 3, 2, 1 );

    assert( populateNextTestCase( network ) == NEW_INPUT && "Should have gotten new input" );
    for( i = 0; i < network->input; ++i ) {
        assert( network->testInputs[i]  == i );
    }
    assert( network->testOutputs[0] == 3 );
    assert( populateNextTestCase( network ) == NEW_INPUT && "Should have gotten new input" );
    for( i = 0; i < network->input; ++i ) {
        assert( network->testInputs[i]  == i + 4 );
    }
    assert( network->testOutputs[0] == 7 );
    assert( populateNextTestCase( network ) == INPUT_WRAPPED && "Should have gotten input after wrapping" );
    for( i = 0; i < network->input; ++i ) {
        assert( network->testInputs[i]  == i );
    }
    assert( network->testOutputs[0] == 3 );
    assert( populateNextTestCase( network ) == NEW_INPUT && "Should have gotten new input" );
}

int main( void ) {
    inputFile = "test_input";
    initInput_test();
    populateNextTestCase_test();

    remove( inputFile );

    exit( EXIT_SUCCESS );
}
