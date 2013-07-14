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
    assert( network->testInputs != NULL && "Should have properly allocated" );
    assert( network->testOutputs != NULL && "Should have properly allocated" );
    assert( network->input == 8 );
    assert( network->hidden == 5 );
    assert( network->output == 8 );
    assert( network->outputWeights == network->hiddenWeights + 40 );
    assert( network->testInputs == network->hiddenWeights + 80 );
    assert( network->testOutputs == network->hiddenWeights + 88 );
    for( i = 0; i < 50; ++i ) {
        assert( network->hiddenWeights[i] != 0 );
        assert( network->outputWeights[i] != 0 );
    }

    network = makeNetwork( 5, 50, 5 );
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
    int *outputs;

    network = setupTestNetwork();

    network->testInputs[0] = 0; network->testInputs[1] = 1;
    outputs = getOutputs( network );
    assert( outputs != NULL && "Should have had some outputs returned" );
    assert( outputs[0] == 4 && outputs[1] == 5 && "Wrong outputs returned" );

    network->testInputs[0] = 2; network->testInputs[1] = 3;
    outputs = getOutputs( network );
    assert( outputs != NULL && "Should have had some outputs returned" );
    assert( outputs[0] == 6 && outputs[1] == 7 && "Wrong outputs returned" );
}

static void train_test( void ) {
    Network *network;

    network = setupTestNetwork();

    network->testInputs[0] = 4; network->testInputs[1] = 5;
    network->testOutputs[0] = 8; network->testOutputs[1] = 9;
    train( network, 1 );

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

