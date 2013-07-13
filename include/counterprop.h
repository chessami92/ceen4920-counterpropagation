typedef struct Network Network;

#define MAX_WEIGHTS 100

struct Network {
    int input, hidden, output;
    int *hiddenWeights, *outputWeights;
    int *testInputs, *testOutputs;
};

int* getOutputs( int *inputs, Network *network );
void train( int *inputs, int *desiredOutputs, Network *network );
Network* makeNetwork( void );
void saveNetwork( Network *network );

