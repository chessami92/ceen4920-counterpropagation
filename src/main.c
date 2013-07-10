#include <stdlib.h>
#include <stdio.h>
#include "counterprop.h"
#include "persistence.h"

extern char *definitionFile;

char *definitionFile;
char trainingFlag;

static int processArguments( int argc, char *argv[] ) {
    int i;
    for( i = 1; i < argc; ++i ) {
        if( argv[i][0] == '-' ) {
            switch( argv[i][1] ) {
                case 'd':
                    definitionFile = argv[i + 1];
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

    if( !processArguments( argc, argv ) ) {
        fprintf( stderr, "Usage: main [-r, -t] [node definition file]\n" );
        exit( EXIT_FAILURE );
    }

    network = makeNetwork();

    saveNetwork( network );

    exit( EXIT_SUCCESS );
}
