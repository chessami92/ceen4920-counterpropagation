#include <stdlib.h>
#include "counterprop.h"
#include "input.h"

const int NEW_INPUT = 1;
const int INPUT_WRAPPED = 0;
const int SEEK_FAILED = -1;

int populateNextTestCase( Network *network ) {
    static int testCaseCount = 0;
    int i;

    for( i = 0; i < network->input; ++i ) {
        network->testInputs[i] = rand() % 256;
    }

    for( i = 0; i < network->output; ++i ) {
        network->testOutputs[i] = 0;
    }

    ++testCaseCount;
    if( testCaseCount < 100 ) {
        return NEW_INPUT;
    } else {
        testCaseCount = 0;
        return INPUT_WRAPPED;
    }
}
