#include <stdlib.h>
#include "counterprop.h"
#include "input.h"

const int NEW_INPUT = 1;
const int INPUT_WRAPPED = 0;
const int SEEK_FAILED = -1;

int populateNextTestCase( Network *network, int *inputs, int *outputs ) {
    static int testCaseCount = 0;
    int input, output;
    int i;

    input = getNumInputs( network );
    output = getNumOutputs( network );

    for( i = 0; i < input; ++i ) {
        inputs[i] = rand() % 256;
    }

    for( i = 0; i < output; ++i ) {
        outputs[0] = 0;
    }

    ++testCaseCount;
    if( testCaseCount < 100 ) {
        return NEW_INPUT;
    } else {
        testCaseCount = 0;
        return INPUT_WRAPPED;
    }
}
