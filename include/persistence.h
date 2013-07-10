#define MAX_WEIGHTS 100

int retrieveNetwork( int *input, int *hidden, int *output, int **hiddenWeights, int **outputWeights );
int persistNetwork( int input, int hidden, int output, int *weights );
