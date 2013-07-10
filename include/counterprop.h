typedef struct Network Network;

int* getOutputs( int *inputs, Network *network );
void train( int *inputs, int *desiredOutputs, Network *network );
Network* makeNetwork( void );
void saveNetwork( Network *network );

