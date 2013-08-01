typedef struct Network Network;

#define MAX_WEIGHTS 500

struct Network {
    int input, hidden, output;
    int *hiddenWeights, *outputWeights;
    int *testInputs, *testOutputs;
};

int* getOutputs( Network *network );
void train( Network *network, int learningRate, int radius );
Network* makeNetwork( int input, int hidden, int output );

