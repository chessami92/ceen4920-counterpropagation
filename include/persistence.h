#define MAX_WEIGHTS 100

int initPersistence( int argc, char *argv[] );
int retrieveNetwork( int *input, int *hidden, int *output, int **hiddenWeights, int **outputWeights );
int persistNetwork( int input, int hidden, int output, int *weights );
