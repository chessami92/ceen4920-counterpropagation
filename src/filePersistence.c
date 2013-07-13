#include <stdlib.h>
#include <stdio.h>
#include "counterprop.h"
#include "persistence.h"

const char *DIMENSION_FORMAT = "InputNodes: %d\nHiddenNodes: %d\nOutputNodes: %d\n";

extern char *definitionFile;

static int retrieveLayerWeights( FILE *fd, int rows, int columns, int *weights );
static void persistLayerWeights( FILE *fd, int rows, int columns, int* weights );

Network* retrieveNetwork( void ) {
    Network *network;
    int input, hidden, output;
    FILE *fd;

    fd = fopen( definitionFile, "r" );

    if( !fd ) {
        fprintf( stderr, "ERROR: Could not open the definition file.\n" );
        return NULL;
    }

    if( fscanf( fd, DIMENSION_FORMAT, &input, &hidden, &output ) != 3 ) {
        fprintf( stderr, "ERROR: Could not parse the layer definitions.\n" );
        return NULL;
    }

    if( input <= 0 || hidden <= 0 || output <= 0 ) {
        fprintf( stderr, "ERROR: Must have positive number of input, hidden, and output nodes.\n" );
        return NULL;
    }

    network = makeNetwork( input, hidden, output );

    fscanf( fd, "Hidden Layer:" );
    if( !retrieveLayerWeights( fd, hidden, input, network->hiddenWeights ) ) {
        return NULL;
    }
    fscanf( fd, "Output Layer:" );
    if( !retrieveLayerWeights( fd, hidden, output, network->outputWeights ) ) {
        return NULL;
    }

    fclose( fd );
    return network;
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

int persistNetwork( Network *network ) {
    FILE *fd;

    fd = fopen( definitionFile, "w" );

    if( !fd ) {
        fprintf( stderr, "ERROR: Could not open definition file for writing.\n" );
        return 0;
    }

    fprintf( fd, DIMENSION_FORMAT, network->input, network->hidden, network->output );

    fprintf( fd, "Hidden Layer:\n" );
    persistLayerWeights( fd, network->hidden, network->input, network->hiddenWeights );
    fprintf( fd, "Output Layer:\n" );
    persistLayerWeights( fd, network->hidden, network->output, network->outputWeights );

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

