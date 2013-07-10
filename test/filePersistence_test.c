#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "persistence.h"

char *definitionFile = "test_definition";

static void cannotOpenFile_test( void ) {
    int weights[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    definitionFile = "";
    assert( persistNetwork( 1, 2, 3, weights ) == 0 && "Shouldn't be able to open null file" );
    definitionFile = "test_definition";
}

static void persistAndLoad_test() {
    int weights[8];
    int *hiddenWeights, *outputWeights;
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
    assert( retrieveNetwork( &input, &hidden, &output, &hiddenWeights, &outputWeights ) == 1 );
    assert( input == 1 && "Input should be re-initialized" );
    assert( hidden == 2 && "Hidden should be re-initialized" );
    assert( output == 3 && "Output should be re-initialized" );
    for( i = 0; i < 2; ++i ) {
        assert( hiddenWeights[i] == i && "Weights should be re-initialized" );
    }
    for( i = 2; i < 8; ++i ) {
        assert( outputWeights[i - 2] == i && "Weights should be re-initialized" );
    }
}

int main( void ) {
    cannotOpenFile_test();
    persistAndLoad_test();

    remove( definitionFile );

    exit( EXIT_SUCCESS );
}
