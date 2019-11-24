#ifndef _UNITTEST_HELPERS_H
#define _UNITTEST_HELPERS_H

void setPlayerHand(int p, int handCount, int *hand, struct gameState *G);
void assertOne(int expected, char *messag);
void assert(int expected, int actual, char *message);
int compareArrays(int *array1, int *array2, int size1, int size2);
int unchangedPlayer(int player, struct gameState *stateAfter, struct gameState *stateBefore);

#endif