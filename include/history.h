typedef struct History History;

#define HISTORY_SIZE 64
#define NUM_HISTORY_COUNTS 3

struct History {
    unsigned char irHistory[HISTORY_SIZE];
    unsigned int historyCount[NUM_HISTORY_COUNTS];
    unsigned char currentHistory;
    unsigned char currentBit;
};

void addHistory( History *history, char currentState );

extern const int HISTORY_AMOUNTS[NUM_HISTORY_COUNTS];

