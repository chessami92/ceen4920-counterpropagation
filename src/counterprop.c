#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "counterprop.h"
#include "persistence.h"

static int findWinningNode( int *inputs, Network *network );
static int* getHiddenWeights( int node, Network *network );
static int* getOutputWeights( int node, Network *network );
static void updateWeights( int count, int *actual, int *desired );

int* getOutputs( int *inputs, Network *network ) {
    int winningNode = findWinningNode( inputs, network );

    return &network->outputWeights[winningNode * network->output];
}

void train( int *inputs, int *desiredOutputs, Network *network ) {
    int winningNode = findWinningNode( inputs, network );
    int *winningWeights = getHiddenWeights( winningNode, network );
    int *outputWeights = getOutputWeights( winningNode, network );

    updateWeights( network->input, inputs, winningWeights );

    updateWeights( network->output, desiredOutputs, outputWeights );
}

static int findWinningNode( int *inputs, Network *network ) {
    int i, j;
    int minimumError, currentError;
    int *currentWeights;
    int winningNode;

    minimumError = INT_MAX;

    for( i = 0; i < network->hidden; ++i ) {
        currentError = 0;
        currentWeights = getHiddenWeights( i, network );
        for( j = 0; j < network->input; ++j ) {
            currentError += abs( inputs[j] - currentWeights[j] );
        }

        if( currentError < minimumError ) {
            winningNode = i;
            minimumError = currentError;
        }
    }

    return winningNode;
}

static int* getHiddenWeights( int hiddenNode, Network *network ) {
    return &network->hiddenWeights[hiddenNode * network->input];
}

static int* getOutputWeights( int hiddenNode, Network *network ) {
    return &network->outputWeights[hiddenNode * network->output];
}

static void updateWeights( int count, int *desired, int *actual ) {
    int i;

    for( i = 0; i < count; ++i ) {
        actual[i] = actual[i] + ( ( desired[i] - actual[i] ) >> 1 );
    }
}

Network* makeNetwork( void ) {
    static Network network;

    if( !retrieveNetwork( &network.input, &network.hidden, &network.output,
    &network.hiddenWeights, &network.outputWeights ) ) {
        return NULL;
    }

    return &network;
}

void saveNetwork( Network *network ) {
    persistNetwork( network->input, network->hidden, network->output, network->hiddenWeights );
}
