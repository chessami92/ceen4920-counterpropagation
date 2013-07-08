typedef struct Network Network;

#define MAX_WEIGHTS 100

int* getOutputs( int *inputs, Network *network );
void train( int *inputs, int *desiredOutputs, Network *network );
Network* makeNetwork( int input, int hidden, int output );

