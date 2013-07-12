#include <stdlib.h>
#include <assert.h>
#include "../src/counterprop.c"

extern int numInput, numHidden, numOutput;

static void makeNetwork_test( void ) {
    Network *network;
    int i;

    numInput = 10; numHidden = 5; numOutput = 10;
    network = makeNetwork();
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

    numInput = 10; numHidden = 7; numOutput = 5;
    network = makeNetwork();
    assert( network == NULL && "Should have not been able to allocate" );
}

static Network* setupTestNetwork( void ) {
    Network *network;
    int i;

    numInput = 2; numHidden = 2; numOutput = 2;
    network = makeNetwork();

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

static void getNumInputsAndOutputs_test( void ) {
    Network *network;

    numInput = 1; numHidden = 2; numOutput = 3;
    network = makeNetwork();

    assert( getNumInputs( network ) == 1 && "Should have one input" );
    assert( getNumOutputs( network ) == 3 && "Should have three outputs" );
}

int main( void ) {
    makeNetwork_test();
    getOutputs_test();
    train_test();
    getNumInputsAndOutputs_test();

    exit( EXIT_SUCCESS );
}

