#include <stdlib.h>
#include <stdio.h>
#include "persistence.h"

const char *DIMENSION_FORMAT = "InputNodes: %d\nHiddenNodes: %d\nOutputNodes: %d\n";

extern char *definitionFile;

static int retrieveLayerWeights( FILE *fd, int rows, int columns, int *weights );
static void persistLayerWeights( FILE *fd, int rows, int columns, int* weights );

int retrieveNetwork( int *input, int *hidden, int *output, int **hiddenWeights, int **outputWeights ) {
    static int weightArray[MAX_WEIGHTS];
    FILE *fd;

    fd = fopen( definitionFile, "r" );

    if( !fd ) {
        fprintf( stderr, "ERROR: Could not open the definition file.\n" );
        return 0;
    }

    if( fscanf( fd, DIMENSION_FORMAT, input, hidden, output ) != 3 ) {
        fprintf( stderr, "ERROR: Could not parse the layer definitions.\n" );
        return 0;
    }

    if( *input * *hidden + *hidden * *output > MAX_WEIGHTS ) {
        fprintf( stderr, "ERROR: Network too large. Adjust MAX_WEIGHTS if necessary." );
        return 0;
    }

    if( !( *input > 0 && *hidden > 0 && *output > 0 ) ) {
        fprintf( stderr, "ERROR: Cannot have 0 for input, hidden nodes, or output nodes.\n" );
        return 0;
    }

    *hiddenWeights = &weightArray[0];
    *outputWeights = &weightArray[*hidden * *input];

    fscanf( fd, "Hidden Layer:" );
    if( !retrieveLayerWeights( fd, *hidden, *input, *hiddenWeights ) ) {
        return 0;
    }
    fscanf( fd, "Output Layer:" );
    if( !retrieveLayerWeights( fd, *hidden, *output, *outputWeights ) ) {
        return 0;
    }

    fclose( fd );
    return 1;
}

static int retrieveLayerWeights( FILE *fd, int rows, int columns, int *weights ) {
    int i;

    for( i = 0; i < rows * columns; ++i ) {
        if( fscanf( fd, "%d ", &weights[i] ) == 0 ) {
            fprintf( stderr, "ERROR: Could not parse weight definitions.\n" );
            return 0;
        }
    }

    return 1;
}

int persistNetwork( int input, int hidden, int output, int *weights ) {
    FILE *fd;

    fd = fopen( definitionFile, "w" );

    if( !fd ) {
        fprintf( stderr, "ERROR: Could not open definition file for writing.\n" );
        return 0;
    }

    fprintf( fd, DIMENSION_FORMAT,
        input, hidden, output );

    fprintf( fd, "Hidden Layer:\n" );
    persistLayerWeights( fd, hidden, input, weights );
    fprintf( fd, "Output Layer:\n" );
    persistLayerWeights( fd, hidden, output, &weights[input * hidden] );

    fclose( fd );

    return 1;
}

static void persistLayerWeights( FILE *fd, int rows, int columns, int* weights ) {
    int i, j;
    int *currentWeights;

    for( i = 0; i < rows; ++i ) {
        currentWeights = &weights[i * columns];
        for( j = 0; j < columns; ++j ) {
            fprintf( fd, "%d ", currentWeights[j] );
        }
        fprintf( fd, "\n" );
    }
}

