#ifndef _RANDOMTEST_HELPERS_H
#define _RANDOMTEST_HELPERS_H
void setPlayerRandomHand(int p, int handCount, struct gameState *G);
int randomNumber(int min, int max);
void assert(int expected, int actual, char *message);
int compareArrays(int *array1, int *array2, int size1, int size2);
int unchangedPlayer(int player, struct gameState *stateAfter, struct gameState *stateBefore);
void setPlayerRandomDeck(int p, int handCount, struct gameState *G);
void setPlayerRandomDiscard(int p, int handCount, struct gameState *G);
int cardIsAction(int card);
int cardIsTreasure(int card);
int cardIsVictory(int card);
void randomInitGame(struct gameState *G);
#endif
