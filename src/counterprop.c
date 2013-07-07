#include <stdlib.h>
#include "counterprop.h"

Network *makeNetwork( int input, int hidden, int output ) {
    static int weightMatrix[MAX_WEIGHTS];
    static Network network;

    if( input * hidden + hidden * output > MAX_WEIGHTS ) {
        return NULL;
    }

    network.hiddenLayer.weights = &weightMatrix[0];
    network.outputLayer.weights = &weightMatrix[input * hidden];
    network.hiddenLayer.winningNode = -1;

    return &network;
}

