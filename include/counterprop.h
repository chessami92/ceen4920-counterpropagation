typedef struct Network Network;

struct Network {
    int *hiddenWeights;
    int *outputWeights;
    int input, hidden, output;
};

int* getOutputs( int *inputs, Network *network );
void train( int *inputs, int *desiredOutputs, Network *network );
int getNumInputs( Network *network );
int getNumOutputs( Network *network );
Network* makeNetwork( void );
void saveNetwork( Network *network );

