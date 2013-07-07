#include <stdlib.h>
#include "counterprop.h"

struct Kohonen {
    int *weights;
    int winningNode;
};

struct Grossberg {
    int *weights;
};

struct Network {
    HiddenLayer *hiddenLayer;
    OutputLayer *outputLayer;
    int input, hidden, output;
};

Network *makeNetwork( int input, int hidden, int output ) {
    static int weightArray[MAX_WEIGHTS];
    static HiddenLayer hiddenLayer;
    static OutputLayer outputLayer;
    static Network network;

    if( input * hidden + hidden * output > MAX_WEIGHTS ) {
        return NULL;
    }

    network.hiddenLayer = &hiddenLayer;
    network.outputLayer = &outputLayer;
    network.input = input;
    network.hidden = hidden;
    network.output = output;

    randomizeWeights( weightArray );
    hiddenLayer.weights = &weightArray[0];
    outputLayer.weights = &weightArray[input * hidden];

    return &network;
}

static void randomizeWeights( int *weights ) {
    int i;

    for( i = 0; i < MAX_WEIGHTS; ++i ) {
        weights[i] = rand() - ( RAND_MAX >> 1 );
    }
}

