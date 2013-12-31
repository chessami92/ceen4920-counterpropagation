#include <stdio.h>
#include "counterprop.h"
#include "input.h"

const int NEW_INPUT = 1;
const int INPUT_WRAPPED = 0;
const int SEEK_FAILED = -1;

extern char *inputFile;

static int populateLayer( int *layer, int num, FILE *fd );

int populateNextTestCase( Network *network ) {
    static FILE *fd = NULL;
    int returnVal;
    char throwAway;

    if( !fd ) {
        fd = fopen( inputFile, "r" );
    }

    returnVal = NEW_INPUT;

    if( fscanf( fd, "\nEO%c", &throwAway ) ) {
        if( fseek( fd, 0, SEEK_SET ) != 0 ) {
            fprintf( stderr, "ERROR: Could not seek to beginning of input file.\n" );
            return SEEK_FAILED;
        }
        returnVal = INPUT_WRAPPED;
    }

    if( !populateLayer( network->testInputs, network->input, fd )
    || !populateLayer( network->testOutputs, network->output, fd ) ) {
        return SEEK_FAILED;
    }

    return returnVal;
}

static int populateLayer( int *layer, int num, FILE *fd ) {
    int i;

    for( i = 0; i < num; ++i ) {
        if( !fscanf( fd, "%d", &layer[i] ) ) {
            fprintf( stderr, "ERROR: Could not parse test case definitions.\n" );
            return 0;
        }
    }

    return 1;
}

