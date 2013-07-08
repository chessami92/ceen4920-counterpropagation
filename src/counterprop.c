#include <stdlib.h>
#include "counterprop.h"

struct Network {
    int *hiddenWeights;
    int *outputWeights;
    int input, hidden, output;
};

Network *makeNetwork( int input, int hidden, int output ) {
    static int weightArray[MAX_WEIGHTS];
    static Network network;

    if( input * hidden + hidden * output > MAX_WEIGHTS ) {
        return NULL;
    }

    network.input = input;
    network.hidden = hidden;
    network.output = output;

    randomizeWeights( weightArray );
    network.hiddenWeights = &weightArray[0];
    network.outputWeights = &weightArray[input * hidden];

    return &network;
}

static void randomizeWeights( int *weights ) {
    int i;

    for( i = 0; i < MAX_WEIGHTS; ++i ) {
        weights[i] = rand() - ( RAND_MAX >> 1 );
    }
}

