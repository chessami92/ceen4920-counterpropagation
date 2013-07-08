typedef struct Network Network;

#define MAX_WEIGHTS 100

int* getOutputs( int *inputs, Network *network );
static int findWinningNode( int *inputs, Network *network );
Network* makeNetwork( int input, int hidden, int output );
static void randomizeWeights( int *weights );

