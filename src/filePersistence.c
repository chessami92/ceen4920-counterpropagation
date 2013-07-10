#include <stdlib.h>
#include <stdio.h>
#include "persistence.h"

const char *DIMENSION_FORMAT = "InputNodes: %d\nHiddenNodes: %d\nOutputNodes: %d\n";

char *fileName;

static int retrieveLayerWeights( FILE *fd, int rows, int columns, int *weights );
static void persistLayerWeights( FILE *fd, int rows, int columns, int* weights );

int initPersistence( int argc, char *argv[] ) {
    fileName = argv[2];

    return 1;
}

int retrieveNetwork( int *input, int *hidden, int *output, int **hiddenWeights, int **outputWeights ) {
    static int weightArray[MAX_WEIGHTS];
    FILE *definitionFile;

    definitionFile = fopen( fileName, "r" );

    if( !definitionFile ) {
        fprintf( stderr, "ERROR: Could not open the definition file.\n" );
        return 0;
    }

    if( fscanf( definitionFile, DIMENSION_FORMAT, input, hidden, output ) != 3 ) {
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

    fscanf( definitionFile, "Hidden Layer:" );
    if( !retrieveLayerWeights( definitionFile, *hidden, *input, *hiddenWeights ) ) {
        return 0;
    }
    fscanf( definitionFile, "Output Layer:" );
    if( !retrieveLayerWeights( definitionFile, *hidden, *output, *outputWeights ) ) {
        return 0;
    }

    fclose( definitionFile );
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
    FILE *definitionFile;

    definitionFile = fopen( fileName, "w" );

    if( !definitionFile ) {
        fprintf( stderr, "ERROR: Could not open definition file for writing.\n" );
        return 0;
    }

    fprintf( definitionFile, DIMENSION_FORMAT,
        input, hidden, output );

    fprintf( definitionFile, "Hidden Layer:\n" );
    persistLayerWeights( definitionFile, hidden, input, weights );
    fprintf( definitionFile, "Output Layer:\n" );
    persistLayerWeights( definitionFile, hidden, output, &weights[input * hidden] );

    fclose( definitionFile );

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

