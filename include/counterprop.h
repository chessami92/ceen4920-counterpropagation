typedef struct Network Network;

#define MAX_WEIGHTS 100

int* getOutputs( int *inputs, Network *network );
void train( int *inputs, int *desiredOutputs, Network *network );
static int findWinningNode( int *inputs, Network *network );
static int updateWeights( int count, int *actual, int *desired );
Network* makeNetwork( int input, int hidden, int output );
static void randomizeWeights( int *weights );

