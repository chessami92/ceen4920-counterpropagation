#include <stdlib.h>
#include <stdio.h>
#include "persistence.h"

int numInput, numHidden, numOutput;

static void randomizeWeights( int *weights );

int retrieveNetwork( int *input, int *hidden, int *output, int **hiddenWeights, int **outputWeights ) {
    static int weightArray[MAX_WEIGHTS];

    *input = numInput;
    *hidden = numHidden;
    *output = numOutput;

    if( *input * *hidden + *hidden * *output > MAX_WEIGHTS ) {
        return 0;
    }

    randomizeWeights( weightArray );
    *hiddenWeights = &weightArray[0];
    *outputWeights = &weightArray[*hidden * *input];

    return 1;
}

int persistNetwork( int input, int hidden, int output, int *weights ) {
    printf( "persistNetwork called with %d, %d, %d, %d", input, hidden, output, weights[0] );
    return 1;
}

static void randomizeWeights( int *weights ) {
    int i;

    for( i = 0; i < MAX_WEIGHTS; ++i ) {
        weights[i] = ( rand() - ( RAND_MAX >> 1 ) ) >> 4;
    }
}
