#include <stdlib.h>
#include <assert.h>
#include "counterprop.h"

static void makeNetwork_test( void ) {
    Network *network;

    network = makeNetwork( 10, 5, 10 );
    assert( network != NULL && "Should have properly allocated" );
    assert( network->hiddenLayer.winningNode == -1 && "Should not have a winner yet" );

    network = makeNetwork( 10, 7, 5 );
    assert( network == NULL && "Should have not been able to allocate" );
}

int main( void ) {
    makeNetwork_test();

    exit( EXIT_SUCCESS );
}

