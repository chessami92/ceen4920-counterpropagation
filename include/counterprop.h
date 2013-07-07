typedef struct Kohonen HiddenLayer;
typedef struct Grossberg OutputLayer;
typedef struct Network Network;

#define MAX_WEIGHTS 100

Network* makeNetwork( int input, int hidden, int output );

