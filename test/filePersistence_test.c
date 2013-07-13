#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "counterprop.h"
#include "persistence.h"

extern char *definitionFile;

char *definitionFile = "test_definition";

static void cannotOpenFile_test( void ) {
    definitionFile = "";
    assert( persistNetwork( NULL ) == 0 && "Shouldn't be able to open null file" );
    definitionFile = "test_definition";
}

static void persistAndLoad_test() {
    Network *network;
    int i;

    network = makeNetwork( 1, 2, 3 );

    for( i = 0; i < 8; ++i ) {
        network->hiddenWeights[i] = i;
    }

    assert( persistNetwork( network ) == 1 );

    network = makeNetwork( 0, 0, 0 );
    network = retrieveNetwork();

    assert( network != NULL );
    assert( network-> input == 1 && "Input should be re-initialized" );
    assert( network->hidden == 2 && "Hidden should be re-initialized" );
    assert( network->output == 3 && "Output should be re-initialized" );
    for( i = 0; i < 2; ++i ) {
        assert( network->hiddenWeights[i] == i && "Weights should be re-initialized" );
    }
    for( i = 2; i < 8; ++i ) {
        assert( network->outputWeights[i - 2] == i && "Weights should be re-initialized" );
    }
}

int main( void ) {
    cannotOpenFile_test();
    persistAndLoad_test();

    remove( definitionFile );

    exit( EXIT_SUCCESS );
}
