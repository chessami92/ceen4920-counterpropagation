#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "counterprop.h"

static int findWinningNode( Network *network );
static int* getHiddenWeights( int node, Network *network );
static int* getOutputWeights( int node, Network *network );
static void updateWeights( int count, int learningRate, int *desired, int *actual );
static void randomizeWeights( int *weights );

int* getOutputs( Network *network ) {
    int winningNode = findWinningNode( network );

    return &network->outputWeights[winningNode * network->output];
}

void train( Network *network, int learningRate, int radius ) {
    int winningNode = findWinningNode( network );
    int *winningWeights = getHiddenWeights( winningNode, network );
    int *winningNeighbor;
    int *outputWeights = getOutputWeights( winningNode, network );
    int i;

    updateWeights( network->input, learningRate, network->testInputs, winningWeights );
    for( i = 1; i < radius + 1; ++i ) {
        winningNeighbor = getHiddenWeights( winningNode - i, network );
        updateWeights( network->input, learningRate + 1, network->testInputs, winningNeighbor );
        winningNeighbor = getHiddenWeights( winningNode + i, network );
        updateWeights( network->input, learningRate + 1, network->testInputs, winningNeighbor );
    }

    updateWeights( network->output, learningRate, network->testOutputs, outputWeights );
}

static int findWinningNode( Network *network ) {
    int i, j;
    int minimumError, currentError;
    int *currentWeights;
    int winningNode;

    minimumError = INT_MAX;
    winningNode = 0;

    for( i = 0; i < network->hidden; ++i ) {
        currentError = 0;
        currentWeights = getHiddenWeights( i, network );
        for( j = 0; j < network->input; ++j ) {
            currentError += abs( network->testInputs[j] - currentWeights[j] );
        }

        if( currentError < minimumError ) {
            winningNode = i;
            minimumError = currentError;
        }
    }

    return winningNode;
}

static int* getHiddenWeights( int hiddenNode, Network *network ) {
    if( hiddenNode < 0 ) {
        return getHiddenWeights( hiddenNode + network->hidden, network );
    } else if( hiddenNode >= network->hidden ) {
        return getHiddenWeights( hiddenNode - network->hidden, network );
    } else {
        return &network->hiddenWeights[hiddenNode * network->input];
    }
}

static int* getOutputWeights( int hiddenNode, Network *network ) {
    return &network->outputWeights[hiddenNode * network->output];
}

static void updateWeights( int count, int learningRate, int *desired, int *actual ) {
    int i;

    for( i = 0; i < count; ++i ) {
        actual[i] = actual[i] + ( ( desired[i] - actual[i] ) >> learningRate );
    }
}

Network* makeNetwork( int input, int hidden, int output ) {
    static Network network;
    static int weightArray[MAX_WEIGHTS];

    if( input * hidden + hidden * output + input + output > MAX_WEIGHTS ) {
        fprintf( stderr, "ERROR: Network too large. Adjust MAX_WEIGHTS if necessary.\n" );
        return NULL;
    }

    randomizeWeights( weightArray );

    network.input = input;
    network.hidden = hidden;
    network.output = output;
    network.hiddenWeights = &weightArray[0];
    network.outputWeights = &network.hiddenWeights[hidden * input];
    network.testInputs = &network.outputWeights[hidden * output];
    network.testOutputs = &network.testInputs[input];

    return &network;
}

static void randomizeWeights( int *weights ) {
    int i;

    for( i = 0; i < MAX_WEIGHTS; ++i ) {
        weights[i] = rand() % 256;
    }
}
