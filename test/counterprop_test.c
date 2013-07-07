#include <stdlib.h>
#include <assert.h>
#include "../src/counterprop.c"

static void makeNetwork_test( void ) {
    Network *network;

    network = makeNetwork( 10, 5, 10 );
    assert( network != NULL && "Should have properly allocated" );
    assert( network->hiddenLayer != NULL && "Should have properly allocated" );
    assert( network->outputLayer != NULL && "Should have properly allocated" );
    assert( network->input == 10 );
    assert( network->hidden == 5 );
    assert( network->output == 10 );
    assert( network->outputLayer->weights == network->hiddenLayer->weights + 50 );

    network = makeNetwork( 10, 7, 5 );
    assert( network == NULL && "Should have not been able to allocate" );
}

int main( void ) {
    makeNetwork_test();

    exit( EXIT_SUCCESS );
}

