#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


void setPlayerHand(int p, int handCount, int *hand, struct gameState *G){
    G->handCount[p] = handCount; 
    for(int i=0; i<handCount; i++){
        G->hand[p][i] = hand[i];
    }
}

void testBaron()
{
    // Game instance
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, baron, smithy};

    initializeGame(2, k, 2, &G);

    // Set current player hand
    
    int currentPlayer = whoseTurn(&G);
    int hand[5] = {copper,copper,copper,copper,copper};
    setPlayerHand(currentPlayer,5,hand,&G);

    baronEffect(&G,1);


}

int main()
{
    testBaron();
    return 0;
}