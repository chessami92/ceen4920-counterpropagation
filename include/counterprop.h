typedef struct Network Network;

#define MAX_WEIGHTS 100

Network* makeNetwork( int input, int hidden, int output );
static void randomizeWeights( int *weights );

