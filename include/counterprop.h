typedef struct Kohonen HiddenLayer;
typedef struct Grossberg OutputLayer;
typedef struct Network Network;

#define MAX_WEIGHTS 100

struct Kohonen {
    int *weights;
    int winningNode;
};

struct Grossberg {
    int *weights;
};

struct Network {
    HiddenLayer hiddenLayer;
    OutputLayer outputLayer;
};

Network* makeNetwork( int input, int hidden, int output );

