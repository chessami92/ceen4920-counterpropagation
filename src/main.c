#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "counterprop.h"
#include "persistence.h"
#include "input.h"

extern char *definitionFile;
extern char *inputFile;

char *definitionFile;
char *inputFile;
char trainingFlag;
int learningRate;

static int processArguments( int argc, char *argv[] ) {
    int i;
    for( i = 1; i < argc; ++i ) {
        if( argv[i][0] == '-' ) {
            switch( argv[i][1] ) {
                case 'd':
                    definitionFile = argv[i + 1];
                    break;
                case 'i':
                    inputFile = argv[i + 1];
                    break;
                case 'l':
                    learningRate = atoi( argv[i + 1] );
                    break;
                case 'r':
                    trainingFlag = 0;
                    break;
                case 't':
                    trainingFlag = 1;
                    break;
                default:
                    fprintf( stderr, "ERROR: Unknown argument: %s\n", argv[i] );
                    return 0;
            }
        }
    }

	if( definitionFile == NULL ) {
	    return 0;
	}

	return 1;
}

int main( int argc, char *argv[] ) {
    Network *network;
    int i;

    srand( time( NULL ) );

    if( !processArguments( argc, argv ) ) {
        fprintf( stderr, "Usage: main [-r, -t] [node definition file]\n" );
        exit( EXIT_FAILURE );
    }

    network = retrieveNetwork();

    if( trainingFlag ) {
        for( i = 0; i < 100; ++i ) {
            populateNextTestCase( network );
            train( network, learningRate );
        }
    }

    persistNetwork( network );

    exit( EXIT_SUCCESS );
}
