#include <stdlib.h>
#include <assert.h>
#include "counterprop.h"
#include "persistence.h"
#include "input.h"

extern int numInput, numHidden, numOutput;

static void populateNextTestCase_test( void ) {
    Network *network;
    int inputs[3], outputs[1];
    int i, j;

    network = makeNetwork( 3, 10, 1 );
    network->testInputs = inputs;
    network->testOutputs = outputs;

    for( i = 0; i < 10000; ++i ) {
        populateNextTestCase( network );
        for( j = 0; j < 3; ++j ) {
            assert( inputs[j] < 256 );
        }
        assert( outputs[0] == 0 );
    }
}

int main( void ) {
    populateNextTestCase_test();

    exit( EXIT_SUCCESS );
}

