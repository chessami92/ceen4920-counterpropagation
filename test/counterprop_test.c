#include <stdlib.h>
#include <assert.h>
#include "../src/counterprop.c"

static void makeNetwork_test( void ) {
    Network *network;
    int i;

    network = makeNetwork( 10, 5, 10 );
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

    network = makeNetwork( 10, 7, 5 );
    assert( network == NULL && "Should have not been able to allocate" );
}

static void getOutputs_test( void ) {
    Network *network;
    int inputs[2], *outputs;
    int i;

    network = makeNetwork( 2, 2, 2 );

    for( i = 0; i < 8; ++i ) {
        network->hiddenWeights[i] = i;
    }

    inputs[0] = 0; inputs[1] = 1;
    outputs = getOutputs( inputs, network );
    assert( outputs != NULL && "Should have had some outputs returned" );
    assert( outputs[0] == 4 && outputs[1] == 5 && "Wrong outputs returned" );

    inputs[0] = 2; inputs[1] = 3;
    outputs = getOutputs( inputs, network );
    assert( outputs != NULL && "Should have had some outputs returned" );
    assert( outputs[0] == 6 && outputs[1] == 7 && "Wrong outputs returned" );
}

int main( void ) {
    makeNetwork_test();
    getOutputs_test();

    exit( EXIT_SUCCESS );
}

