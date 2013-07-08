#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "counterprop.h"

struct Network {
    int *hiddenWeights;
    int *outputWeights;
    int input, hidden, output;
};

static int findWinningNode( int *inputs, Network *network );
static int updateWeights( int count, int *actual, int *desired );
static void randomizeWeights( int *weights );

int* getOutputs( int *inputs, Network *network ) {
    int winningNode = findWinningNode( inputs, network );

    return &network->outputWeights[winningNode * network->output];
}

void train( int *inputs, int *desiredOutputs, Network *network ) {
    int winningNode = findWinningNode( inputs, network );

    updateWeights( network->input, inputs,
    &network->hiddenWeights[winningNode * network->input] );

    updateWeights( network->output, desiredOutputs,
    &network->outputWeights[winningNode * network->output] );
}

static int findWinningNode( int *inputs, Network *network ) {
    int i, j;
    int minimumError, currentError;
    int weight;
    int winningNode;

    minimumError = INT_MAX;

    for( i = 0; i < network->hidden; ++i ) {
        currentError = 0;
        for( j = 0; j < network->input; ++j ) {
            weight = network->hiddenWeights[i * network->input + j];
            currentError += abs( inputs[j] - weight );
        }

        if( currentError < minimumError ) {
            winningNode = i;
            minimumError = currentError;
        }
    }

    return winningNode;
}

static int updateWeights( int count, int *desired, int *actual ) {
    int i;

    for( i = 0; i < count; ++i ) {
        actual[i] = actual[i] + ( ( desired[i] - actual[i] ) >> 1 );
    }
}

Network* makeNetwork( int input, int hidden, int output ) {
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
        weights[i] = rand() - ( RAND_MAX >> 1 ) >> 4;
    }
}

