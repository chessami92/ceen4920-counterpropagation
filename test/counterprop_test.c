#include <stdlib.h>
#include <assert.h>
#include "counterprop.h"

static void makeNetwork_test( void ) {
    Network *network;
    int i;

    network = makeNetwork( 8, 5, 8 );
    assert( network != NULL && "Should have properly allocated" );
    assert( network->hiddenWeights != NULL && "Should have properly allocated" );
    assert( network->outputWeights != NULL && "Should have properly allocated" );
    assert( network->input == 10 );
    assert( network->hidden == 5 );
    assert( network->output == 10 );
    assert( network->outputWeights == network->hiddenWeights + 50 );
    for( i = 0; i < 50; ++i ) {
        assert( network->hiddenWeights[i] != 0 );
        assert( network->outputWeights[i] != 0 );
    }

    network = makeNetwork( 10, 5, 10 );
    assert( network == NULL && "Should have not been able to allocate" );
}

static Network* setupTestNetwork( void ) {
    Network *network;
    int i;

    network = makeNetwork( 2, 2, 2 );

    for( i = 0; i < 8; ++i ) {
        network->hiddenWeights[i] = i;
    }

    return network;
}

static void getOutputs_test( void ) {
    Network *network;
    int inputs[2], *outputs;

    network = setupTestNetwork();

    inputs[0] = 0; inputs[1] = 1;
    outputs = getOutputs( inputs, network );
    assert( outputs != NULL && "Should have had some outputs returned" );
    assert( outputs[0] == 4 && outputs[1] == 5 && "Wrong outputs returned" );

    inputs[0] = 2; inputs[1] = 3;
    outputs = getOutputs( inputs, network );
    assert( outputs != NULL && "Should have had some outputs returned" );
    assert( outputs[0] == 6 && outputs[1] == 7 && "Wrong outputs returned" );
}

static void train_test( void ) {
    Network *network;
    int inputs[2], outputs[2];

    network = setupTestNetwork();

    inputs[0] = 4; inputs[1] = 5;
    outputs[0] = 8; outputs[1] = 9;
    train( inputs, outputs, network );

    assert( network->hiddenWeights[2] == 3 && network->hiddenWeights[3] == 4
    && "Should have updated the Kohonen layer weights" );
    assert( network->outputWeights[2] == 7 && network->outputWeights[3] == 8
    && "Should have updated the Grossberg layer weights" );
}

int main( void ) {
    makeNetwork_test();
    getOutputs_test();
    train_test();

    exit( EXIT_SUCCESS );
}

