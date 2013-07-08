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

int main( void ) {
    makeNetwork_test();

    exit( EXIT_SUCCESS );
}

